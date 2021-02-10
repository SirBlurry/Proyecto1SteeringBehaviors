#pragma once
#include"agent.h"

class Follower : public Agent
{
private:
public:
	float perceptionRadious;
	Follower() {}
	Follower(float p, vector2 mf)
	{
		perceptionRadious = p;
		Agent::maxForce = mf;
	}
	Follower(float prcptn, vector2 pos, vector2 vel, vector2 maxFrc, float maxV, float mss, float r, float w, float h) :
		perceptionRadious(prcptn), Agent(pos, vel, maxFrc, maxV, mss, r, w, h) {}
	void manager(Agent*, list<Obstacle*>&);
	bool perception(Agent*);
};