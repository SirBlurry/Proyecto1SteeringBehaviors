//#include "sBehaviours.h"
#include "agent.h"

void Agent::sBehaviours::wander(Agent* self, float vista, time_t* deltaTime) {
	int rango = 1000;
	self->setRadarRadius(vista);
	self->radarCenter() = self->velocity;
	self->radarCenter().normalizar();
	self->radarCenter().multiEscalar(vista);
	self->radarCenter() += self->position;

	if (*deltaTime == 1) canChange = true;
	if ((*deltaTime == 0 && canChange) || self->doIt) 
	{
		displacement = vector2((rand() % (rango * 2 + 1)) - rango, (rand() % (rango * 2 + 1)) - rango);
		canChange = false;
		if (self->doIt) { self->doIt = false; }
	}
	seek(self, displacement);
}

void Agent::sBehaviours::arrival(Agent* owner, vector2 target, float slowArea)
{
	vector2 firstCenter = owner->radarCenter();
	owner->setRadarRadius(slowArea);
	vector2 desired_vel = target - owner->position;
	vector2 slowLimit = target - owner->position;
	desired_vel.normalizar();
	if (owner->radar->detect(target, slowArea))
	{
		owner->radarCenter() = target;
		desired_vel.multiEscalar(owner->maxVel * (slowLimit.getMagnitud() / slowArea));
		if (!owner->radar->detect(owner->position, slowArea))
		{
			owner->radarCenter() = firstCenter;
			desired_vel.multiEscalar(owner->maxVel);
		}
	}
	vector2 steering = vector2::resta(desired_vel, owner->velocity);
	steering = vector2::truncar(steering, owner->maxForce.getMagnitud());
	steering.dividirEscalar(owner->mass);
	owner->velocity = vector2::truncar((steering + owner->velocity), owner->maxVel);
	owner->position += owner->velocity;
}

void Agent::sBehaviours::interpose(Agent* self, Agent* target1, Agent* target2)
{
	vector2 middle = target1->position + target2->position;
	middle.dividirEscalar(2.0f);
	vector2 time = self->position - middle;
	time.dividirEscalar(self->maxVel);
	float timeToIntercept = time.getMagnitud();
	if (self->radar->detect(time, self->getRadarRadius()))
	{
		arrival(self, middle, middle.getMagnitud());
	}
	else
	{
		seek(self, middle);
	}
	vector2 firstPos = target1->position + target1->velocity;
	firstPos.multiEscalar(timeToIntercept);
	vector2 secondPos = target2->position + target2->velocity;
	secondPos.multiEscalar(timeToIntercept);
	middle = firstPos - secondPos;
	middle.dividirEscalar(2.0f);
}

void Agent::sBehaviours::seek(Agent* self, vector2 target)
{
	vector2 v = vector2(0, 0);
	vector2 desired_vel = target - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);

	vector2 steering = desired_vel - self->velocity;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::obstacleAvoidance(Agent* self, Obstacle* obstacle)
{
	vector2 avoid;
	if (self->radar->detect(obstacle->position, obstacle->getLenght()))
	{
		avoid = self->radarCenter() - obstacle->getMinorDistance(self->velocity);
		avoid.normalizar();
		avoid.multiEscalar(self->maxVel);
	}
	else
	{
		avoid.multiEscalar(0.0f);
	}
	avoid = self->radarCenter() - obstacle->getMinorDistance(self->velocity);
	avoid.normalizar();
	avoid.multiEscalar(self->maxVel);

	vector2 steering = self->velocity + avoid;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::wallAvoidance(Agent* self, Obstacle* obstacle)
{
	vector2 avoid;
	if (self->radar->detect(obstacle->position, obstacle->getLenght()))
	{
		avoid = self->radarCenter() + obstacle->getNearPoint(self->velocity);
		avoid.normalizar();
		avoid.multiEscalar(self->maxVel);
	}
	else
	{
		avoid.multiEscalar(0.0f);
	}
	avoid = self->radarCenter() + obstacle->getNearPoint(self->velocity);
	avoid.normalizar();
	avoid.multiEscalar(self->maxVel);

	vector2 steering = self->velocity + avoid;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::pathFollowing(Agent* self, list<vector2>* nodes)
{
	if (!nodes->empty())
	{
		vector2 current = nodes->front();
		vector2 distance = current - self->position;
		if (self->radar->detect(current, 5.0f))
		{
			nodes->pop_front();
			nodes->push_back(current);
		}
		seek(self, current);
	}
}

void Agent::sBehaviours::flee(Agent* self, Agent* target)
{
	vector2 desired_vel = target->position - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);

	vector2 steering = desired_vel - self->velocity;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position -= self->velocity;
}

void Agent::sBehaviours::OffsetPursuit(Agent* self, float offset, Agent* target)
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

void Agent::sBehaviours::Hide(Agent* self, list<Obstacle*>& objects, Agent* target) {
	float disToClosest = 1000;
	vector2 bestHiding;
	for (Obstacle* obj : objects) {
		vector2 hidingSpot = obj->getMinorDistance(self->position);
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
	self->radarCenter() = bestHiding;
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