#include "agent.h"

Agent::Agent(vector2 pos, vector2 vel, float maxV, float mss) {
	position = pos;
	velocity = vel;
	maxVel = maxV;
	mass = mss;
}