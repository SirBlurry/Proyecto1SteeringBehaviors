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

void BBehaviours::Wander(Agent* self, float vista, time_t* deltaTime)
{
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
		if (self->doIt) self->doIt = false;
	}
	self->Displ = guide;
	vector2 steering = guide + displacement;
	//cout << "steer: " << steering.x << ", " << steering.y << endl;
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
