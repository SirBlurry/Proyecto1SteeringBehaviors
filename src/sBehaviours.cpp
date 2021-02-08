//#include "sBehaviours.h"
#include "agent.h"

void Agent::sBehaviours::wander(Agent* self, float vista, time_t* deltaTime) {
	int rango = 1000;
	vector2 guide = self->velocity;
	guide.normalizar();
	guide.multiEscalar(vista);
	guide += self->position;
	if (*deltaTime == 1) canChange = true;
	if ((*deltaTime == 0 && canChange) || self->doIt) {
		displacement = vector2((rand() % (rango * 2 + 1)) - rango, (rand() % (rango * 2 + 1)) - rango);
		//cout << displacement.x << ", " << displacement.y << ", " << *deltaTime << endl;
		canChange = false;
		if(self->doIt) self->doIt = false;
	}
	self->Displ = guide;
	vector2 steering = guide + displacement;
	//cout << "steer: " << steering.x << ", " << steering.y << endl;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::arrival(Agent* owner, Agent* target)
{
	owner->radar->center = target->position;
	owner->radar->radius = 100.0f;
	vector2 desired_vel = target->position - owner->position;
	vector2 slowLimit = target->position - owner->position;
	float agentMaxVel = owner->maxVel;
	desired_vel.normalizar();
	/*if (slowLimit.getMagnitud() < owner->radar->radius)*/
	if (owner->radar->detect(slowLimit))
	{
		desired_vel.multiEscalar(agentMaxVel * (desired_vel.getMagnitud() / owner->radar->radius));
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