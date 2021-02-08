#pragma once
#include"agent.h"

class Greedy : public Agent
{
private:
public:
	float perceptionRadious;
	Greedy() {}
	Greedy(float p, vector2 mf)
	{
		perceptionRadious = p;
		Agent::maxForce = mf;
	}
	Greedy(float prcptn, vector2 pos, vector2 vel, vector2 maxFrc, float maxV, float mss, float r) :
		perceptionRadious(prcptn), Agent(pos, vel, maxFrc, maxV, mss, r) {}
	void manager(list<Agent*>&, time_t*);
	bool perception(Agent*);
};