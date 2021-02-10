#pragma once
#include"agent.h"

class Patrol : public Agent
{
private:
public:
	float perceptionRadious;
	Patrol() {}
	Patrol(float p, vector2 mf)
	{
		perceptionRadious = p;
		Agent::maxForce = mf;
	}
	Patrol(float prcptn, vector2 pos, vector2 vel, vector2 maxFrc, float maxV, float mss, float r, float w, float h) :
		perceptionRadious(prcptn), Agent(pos, vel, maxFrc, maxV, mss, r, w, h) {}
	void manager(list<Agent*>&, list<vector2>&, list<Obstacle*>&);
	bool perception(Agent*);
};

