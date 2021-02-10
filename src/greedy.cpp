#include "greedy.h"

void Greedy::manager(list<Agent*>& agents, time_t* deltaTime)
{
	this->setRadarRadius(120.0f);
	this->radarCenter() = this->velocity;
	this->radarCenter().normalizar();
	this->radarCenter().multiEscalar(80.0f);
	this->radarCenter() += this->position;
	for (Agent* ag : agents)
	{
		/*if ((Agent::position - ag->position).getMagnitud() < perceptionRadious)
		{
			Agent::sb->seek(this, ag);
			return;
		}*/
		if ((ag != this) && (this->radar->detect(ag->position, ag->lenght)
			|| this->radar->detect(ag->getP0(), ag->lenght)
			|| this->radar->detect(ag->getP1(), ag->lenght)
			|| this->radar->detect(ag->getP2(), ag->lenght)
			|| this->radar->detect(ag->getP3(), ag->lenght))/*perception(ag)*/)
		{
			if (ag->width < 70.0f)
			{
				Agent::sb->arrival(this, ag->position, 120);
				return;
			}
			else
			{
				Agent::sb->obstacleAvoidance(this, position, agents);
				return;
			}
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