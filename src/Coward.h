#pragma once
#include "agent.h"

class Coward : public Agent
{
private:
public:
	float perceptionRadious;
	Coward() {}
	Coward(float p, vector2 mf)
	{
		perceptionRadious = p;
		Agent::maxForce = mf;
	}
	Coward(float prcptn, vector2 pos, vector2 vel, vector2 maxFrc, float maxV, float mss, float r, float w, float h) :
		perceptionRadious(prcptn), Agent(pos, vel, maxFrc, maxV, mss, r, w, h) {}
	void manager(list<Agent*>&, list<Obstacle*>&, time_t*);
	bool perception(Agent*);
};