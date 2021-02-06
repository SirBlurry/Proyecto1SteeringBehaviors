#pragma once
#include"vector2.h"

class Agent {
	private:
	public:
		float maxVel = 0, mass = 0;
		vector2 position = vector2(0,0);
		vector2 velocity = vector2(0,0);
		vector2 maxForce = vector2(10, 10);
		Agent() {}
		Agent(vector2, vector2, float, float);
};


