#include "sBehaviours.h"

void sBehaviours::seek(Agent* agnt, Agent* target) {
	//vector2 desired_vel = vector2::resta(target->position, agnt->position);
	vector2 desired_vel = target->position - agnt->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(agnt->maxVel);
	vector2 steering = vector2::resta(desired_vel, agnt->velocity);
	steering = vector2::truncar(steering, agnt->maxForce.getMagnitud());
	steering.dividirEscalar(agnt->mass);
	
	agnt->velocity = vector2::truncar((steering+agnt->velocity), agnt->maxVel);
	agnt->position += agnt->velocity;
}