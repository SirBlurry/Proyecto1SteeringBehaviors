#include "agent.h"


/**
* @brief (posición, velocidad, maxVel, masa)
*/
Agent::Agent(vector2 pos, vector2 vel, float maxV, float mss) {
	position = pos;
	velocity = vel;
	maxVel = maxV;
	mass = mss;
	//sb = sBehaviours();
}

/**
* @brief (posición, velocidad, maxForce, maxVel, masa)
*/
Agent::Agent(vector2 pos, vector2 vel, vector2 mF, float maxV, float mss, float r) {
	position = pos;
	velocity = vel;
	maxForce = mF;
	maxVel = maxV;
	radious = r;
	mass = r / 3;
}

Agent::Agent(vector2 pos, vector2 vel, float maxV, float mss, vector2 radCenter, float radR)
{
	position = pos;
	velocity = vel;
	maxVel = maxV;
	mass = mss;
	radar->center = radCenter;
	radar->radius = radR;
}

Agent::Agent(vector2 pos, vector2 vel, vector2 mF, float maxV, float mss, float r, vector2 radCenter, float radR)
{
	position = pos;
	velocity = vel;
	maxForce = mF;
	maxVel = maxV;
	radious = r;
	mass = r / 3;
	radar->center = radCenter;
	radar->radius = radR;
}

vector2& Agent::radarCenter()
{
	return radar->center;
}

void Agent::setRadarRadius(float rad)
{
	radar->radius = rad;
}

float Agent::getRadarRadius()
{
	return radar->radius;
}


bool Agent::limits() {
	bool bandera = false;
	if (position.x >= ofGetWidth()) {
		position.x = 0;
		position.generarMagnitud();
		bandera = true;
	}
	if (position.x < -3) {
		position.x = ofGetWidth();
		position.generarMagnitud();
		bandera = true;
	}
	if (position.y >= ofGetHeight()) {
		position.y = 0;
		position.generarMagnitud();
		bandera = true;
	}
	if (position.y < -3) {
		position.y = ofGetHeight();
		position.generarMagnitud();
		bandera = true;
	}
	return bandera;
}