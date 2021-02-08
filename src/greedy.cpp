#include "greedy.h"

void Greedy::manager(list<Agent*>& agents, time_t* deltaTime)
{
	for (Agent* ag : agents)
	{
		/*if ((Agent::position - ag->position).getMagnitud() < perceptionRadious)
		{
			Agent::sb->seek(this, ag);
			return;
		}*/
		if ((ag != this) && this->radar->detect(ag->position, ag->radious)/*perception(ag)*/)
		{
			Agent::sb->arrival(this, ag, 80);
			return;
		}
	}
	sb->wander(this, 120, deltaTime);
	Agent::doIt = Agent::limits();
}

bool Greedy::perception(Agent* trgt)
{
	vector2 view = velocity;
	view.normalizar();
	view.multiEscalar(120);
	view += position;

	bool viewed = (trgt->position - view).getMagnitud() < perceptionRadious + trgt->radious;
	if (viewed) { this->Displ = view; }
	return viewed;
}
