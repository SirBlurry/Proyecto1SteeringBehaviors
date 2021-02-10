#pragma once
#include"agent.h"

class Runner : public Agent
{
private:
public:
	float perceptionRadious;
	Runner() {}
	Runner(float p, vector2 mf)
	{
		perceptionRadious = p;
		Agent::maxForce = mf;
	}
	Runner(float prcptn, vector2 pos, vector2 vel, vector2 maxFrc, float maxV, float mss, float r, float w, float h, vector2 rad, float radR) :
		perceptionRadious(prcptn), Agent(pos, vel, maxFrc, maxV, mss, r, w, h, rad, radR) {}
	void manager(list<Agent*>&, list<vector2>&);
	bool perception(Agent*);
};