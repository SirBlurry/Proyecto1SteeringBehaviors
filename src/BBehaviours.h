#pragma once
#include "agent.h"

class BBehaviours {
private:
	bool canChange = true;
	vector2 displacement = vector2(0, 0);
public:
	void Evade(Agent*, Agent*);
	void Pursuit(Agent*, Agent*);
	void Wander(Agent*, float, time_t*);
	void WallAvoidance(Agent*, Agent*);
	void Hide(Agent*, Agent*);
	void OffsetPursuit(Agent*, Agent*);
	BBehaviours() { displacement = vector2(rand() % 101 - 50, rand() % 101 - 50); }
};
