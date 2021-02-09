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

void Agent::sBehaviours::seek(Agent* self, Agent* target)
{
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

void Agent::sBehaviours::obstacleAvoidance(Agent* self, vector2 destiny, list<Agent*>& agents)
{
	float dynamicL = self->velocity.getMagnitud() / self->maxVel;
	vector2 velNor = self->velocity;
	velNor.normalizar();
	vector2 head = self->position - velNor;
	head.multiEscalar(dynamicL);

	vector2 head2 = head;
	head2.multiEscalar(dynamicL * 0.5f);

	vector2 objPos;
	vector2 avoid;

	for (Agent* ag : agents)
	{
		objPos = ag->position;
		if (self->radar->detect(objPos, ag->lenght))
		{
			avoid = head - objPos;
			avoid.normalizar();
			avoid.multiEscalar(self->maxForce.getMagnitud());
			self->velocity = avoid;
		}
		else
		{
			avoid.multiEscalar(0.0f);
		}
	}
	vector2 steering = self->radarCenter() - avoid;
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

//void sBehaviours::seek(Agent* agnt, Agent* target) {
//
//	vector2 v = vector2(0, 0);
//	//vector2 desired_vel = vector2::resta(target->position, agnt->position);
//	vector2 desired_vel = target->position - agnt->position;
//	desired_vel.normalizar();
//	desired_vel.multiEscalar(agnt->maxVel);
//	vector2 steering = vector2::resta(desired_vel, agnt->velocity);
//	steering = vector2::truncar(steering, agnt->maxForce.getMagnitud());
//	steering.dividirEscalar(agnt->mass);
//	
//	agnt->velocity = vector2::truncar((steering+agnt->velocity), agnt->maxVel);
//	agnt->position += agnt->velocity;
//}