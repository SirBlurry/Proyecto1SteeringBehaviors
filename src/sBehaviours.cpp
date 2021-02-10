//#include "sBehaviours.h"
#include "agent.h"

void Agent::sBehaviours::wander(Agent* self, float vista, time_t* deltaTime) {
	int rango = 1000;
	self->setRadarRadius(vista);
	self->radarCenter() = self->velocity;
	self->radarCenter().normalizar();
	self->radarCenter().multiEscalar(vista);
	self->radarCenter() += self->position;

	/*vector2 guide = self->velocity;
	guide.normalizar();
	guide.multiEscalar(vista);
	guide += self->position;*/
	if (*deltaTime == 1) canChange = true;
	if ((*deltaTime == 0 && canChange) || self->doIt) {
		displacement = vector2((rand() % (rango * 2 + 1)) - rango, (rand() % (rango * 2 + 1)) - rango);
		//cout << displacement.x << ", " << displacement.y << ", " << *deltaTime << endl;
		canChange = false;
		if(self->doIt) self->doIt = false;
	}
	self->Displ = self->radarCenter();
	vector2 steering = self->radarCenter() + displacement;
	/*self->Displ = guide;
	vector2 steering = guide + displacement;*/
	//cout << "steer: " << steering.x << ", " << steering.y << endl;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::arrival(Agent* owner, Agent* target, float slowArea)
{
	vector2 firstCenter = owner->radarCenter();
	float firstRad = owner->getRadarRadius();

	owner->radarCenter() = target->position;
	owner->setRadarRadius(slowArea);

	vector2 desired_vel = target->position - owner->position;
	vector2 slowLimit = target->position - owner->position;
	float agentMaxVel = owner->maxVel;
	desired_vel.normalizar();
	/*if (slowLimit.getMagnitud() < owner->radar->radius)*/
	if (owner->radar->detect(target->position, target->radious))
	{
		desired_vel.multiEscalar(agentMaxVel * (slowLimit.getMagnitud() / slowArea));
		owner->radarCenter() = firstCenter;
		owner->setRadarRadius(firstRad);
	}
	else
	{
		desired_vel.multiEscalar(agentMaxVel);
	}
	vector2 steering = vector2::resta(desired_vel, owner->velocity);
	steering = vector2::truncar(steering, owner->maxForce.getMagnitud());
	steering.dividirEscalar(owner->mass);

	owner->velocity = vector2::truncar((steering + owner->velocity), agentMaxVel);
	owner->position += owner->velocity;
}

void Agent::sBehaviours::seek(Agent* self, Agent* target) {
	vector2 v = vector2(0, 0);
	vector2 desired_vel = target->position - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);

	vector2 steering = desired_vel - self->velocity;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::flee(Agent* self, Agent* target) {
	vector2 v = vector2(0, 0);
	vector2 desired_vel = target->position - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);

	vector2 steering = desired_vel - self->velocity;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position -= self->velocity;
}

void Agent::sBehaviours::OffsetPursuit(Agent* self, float offset, Agent*target)
{
	vector2 targetvel = target->velocity;
	targetvel.multiEscalar(-1);
	targetvel.normalizar();
	targetvel.multiEscalar(offset);
	vector2 behind = target->position + targetvel;

	vector2 firstCenter = self->radarCenter();
	self->radarCenter() = behind;
	self->setRadarRadius(offset);
	vector2 desired_vel = behind - self->position;
	float distance = desired_vel.getMagnitud();
	desired_vel.normalizar();
	if (distance < self->getRadarRadius()) {
		desired_vel.multiEscalar( self->maxVel * (distance / self->getRadarRadius()));
	}
	else{
		desired_vel.multiEscalar(self->maxVel);
	}
	vector2 steering = vector2::resta(desired_vel, self->velocity);
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;

}

void Agent::sBehaviours::WallAvoidance(Agent* self, list<Agent*>& objects, float maxAhead)
{
	vector2 agentVel = self->velocity;
	agentVel.normalizar();
	//agentVel.multiEscalar(maxAhead);
	float dynamic_length = self->velocity.getMagnitud() / self->maxVel;
	agentVel.multiEscalar(dynamic_length);
	vector2 ahead = self->position + agentVel;
	vector2 ahead2 = ahead;
	ahead2.multiEscalar(0.5);
	vector2 P0, P3, distance, minorDis;
	for (Agent* obj : objects) {
		P0 = obj->getP0();
		P3 = obj->getP3();
		if (ahead.x > P0.x && ahead.x < P3.x && ahead.y > P0.y && ahead.y < P3.y ||
			ahead2.x > P0.x && ahead2.x < P3.x && ahead2.y > P0.y && ahead2.y < P3.y) {
		distance = ahead - obj->position;
		minorDis = obj->getMinorDistance(ahead);
			//minorDis.normalizar();

			/*vector2 disP1(P1 - ahead), disP2(P2 - ahead), disP3(P3 - ahead), disP4(P4 - ahead);
			vector2 nearestP;
			float shortLength;
			float length[4] = { disP1.getMagnitud(),disP2.getMagnitud,disP3.getMagnitud(),disP4.getMagnitud() };
			for (short i = 0; i < 4; i++) {
				if (length[i] == length[0]) {
					shortLength = length[i];
				}
				else if (length[i] < shortLength) {
					shortLength = length[i];
				}
			}*/
			//minorDis.normalizar();
			//minorDis.multiEscalar(self->maxForce.getMagnitud());
			//self->velocity = minorDis;
			//distance.multiEscalar(2);
			vector2 desired_vel = (minorDis +distance) - self->position;
			desired_vel.normalizar();
			desired_vel.multiEscalar(self->maxVel);
			//distance.normalizar();
			//distance.multiEscalar(1000);
			vector2 steering;
			//steering += distance;
			//steering += minorDis;
			steering = vector2::resta(desired_vel, self->velocity);
			steering = vector2::truncar(steering, self->maxForce.getMagnitud());
			steering.dividirEscalar(self->mass);

			self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
			self->position += self->velocity;
		}
	}

}
vector2 Agent::sBehaviours::GetHidingPosition(Agent* object, Agent* target) {
	float disObj = 30;
	float distAway;
	vector2 distObj = object->position - target->position;
	distObj.normalizar();
	distObj.multiEscalar(distAway);
	return distObj + object->position;

	//float distanceAway = 
}
void Agent::sBehaviours::Hide(Agent* self, list<Agent*>& objects, Agent* target) {
	float disToClosest = 1000;
	vector2 bestHiding;
	for (Agent* obj : objects) {
		vector2 hidingSpot = GetHidingPosition(obj, target);
		float distance = hidingSpot.getMagnitud();
		if (distance < disToClosest) {
			disToClosest = distance;
			bestHiding = hidingSpot;
		}
	}
	if (disToClosest == 1000) {
		Evade(self, target);
		return;
	}
	vector2 firstCenter = self->radarCenter();
	self->radarCenter = bestHiding;
	self->setRadarRadius(50);
	vector2 desired_vel = bestHiding - self->position;
	float distance = desired_vel.getMagnitud();
	desired_vel.normalizar();
	if (distance < self->getRadarRadius()) {
		desired_vel.multiEscalar(self->maxVel * (distance / self->getRadarRadius()));
	}
	else {
		desired_vel.multiEscalar(self->maxVel);
	}
	vector2 steering = vector2::resta(desired_vel, self->velocity);
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;

}
void Agent::sBehaviours::Evade(Agent* self, Agent* target)
{
	float T;
	vector2 distance = target->position - self->position;
	T = distance.getMagnitud() / self->maxVel;
	vector2 targetvel = target->velocity;
	targetvel.multiEscalar(T);
	vector2 futurePos = target->position + targetvel;
	vector2 desired_vel = futurePos - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);
	vector2 steering = vector2::resta(desired_vel, self->velocity);
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position -= self->velocity;

}

void Agent::sBehaviours::Pursuit(Agent* self, Agent* target)
{
	float T;
	vector2 distance = target->position - self->position;
	T = distance.getMagnitud() / self->maxVel;
	vector2 targetvel = target->velocity;
	targetvel.multiEscalar(T);
	vector2 futurePos = target->position + targetvel;
	vector2 desired_vel = futurePos - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);
	vector2 steering = vector2::resta(desired_vel, self->velocity);
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;

}
