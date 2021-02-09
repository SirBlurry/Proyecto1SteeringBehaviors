#include "agent.h"

Agent::Agent(vector2 pos, float w, float h)
{
	position = pos;
	width = w;
	height = h;
}

/**
* @brief (posición, velocidad, maxVel, masa)
*/
Agent::Agent(vector2 pos, vector2 vel, float maxV, float mss, float w, float h) {
	position = pos;
	velocity = vel;
	maxVel = maxV;
	mass = mss;
	width = w;
	height = h;
	getP0();
	getP1();
	getP2();
	getP3();
	getLenght();
	//sb = sBehaviours();
}

/**
* @brief (posición, velocidad, maxForce, maxVel, masa)
*/
Agent::Agent(vector2 pos, vector2 vel, vector2 mF, float maxV, float mss, float r, float w, float h) {
	position = pos;
	velocity = vel;
	maxForce = mF;
	maxVel = maxV;
	radious = r;
	mass = r / 3;
	width = w;
	height = h;
	getP0();
	getP1();
	getP2();
	getP3();
	getLenght();
}

Agent::Agent(vector2 pos, vector2 vel, float maxV, float mss, float w, float h, vector2 radCenter, float radR)
{
	position = pos;
	velocity = vel;
	maxVel = maxV;
	mass = mss;
	width = w;
	height = h;
	radar->center = radCenter;
	radar->radius = radR;
}

Agent::Agent(vector2 pos, vector2 vel, vector2 mF, float maxV, float mss, float r, float w, float h, vector2 radCenter, float radR)
{
	position = pos;
	velocity = vel;
	maxForce = mF;
	maxVel = maxV;
	radious = r;
	mass = r / 3;
	width = w;
	height = h;
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