#include "BBehaviours.h"

void BBehaviours::Evade(Agent* self, Agent* target)
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

void BBehaviours::Pursuit(Agent* self, Agent* target)
{
	float T;
	vector2 distance = target->position - self->position;
	T = distance.getMagnitud()/self->maxVel;
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


void BBehaviours::WallAvoidance(Agent*, Agent*)
{
}

void BBehaviours::Hide(Agent*, Agent*)
{
}

void BBehaviours::OffsetPursuit(Agent*, Agent*)
{
}
