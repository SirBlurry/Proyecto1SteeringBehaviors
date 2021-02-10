#include "Patrol.h"

void Patrol::manager(list<Agent*>& agents, list<vector2>& path)
{
	this->setRadarRadius(35.0f);
	this->radarCenter() = this->velocity;
	this->radarCenter().normalizar();
	this->radarCenter().multiEscalar(35.0f);
	this->radarCenter() += this->position;

	for (Agent* ag : agents)
	{
		if ((ag != this) && (this->radar->detect(ag->position, ag->lenght)
			|| this->radar->detect(ag->getP0(), ag->lenght)
			|| this->radar->detect(ag->getP1(), ag->lenght)
			|| this->radar->detect(ag->getP2(), ag->lenght)
			|| this->radar->detect(ag->getP3(), ag->lenght))/*perception(ag)*/)
		{
			Agent::sb->obstacleAvoidance(this, position, agents);
			return;
		}
	}
	sb->pathFollowing(this, &path);
	Agent::doIt = Agent::limits();
}

bool Patrol::perception(Agent* trgt)
{
	vector2 view = velocity;
	view.normalizar();
	view.multiEscalar(120);
	view += position;

	bool viewed = (trgt->position - view).getMagnitud() < perceptionRadious + trgt->radious;
	if (viewed) { this->Displ = view; }
	return viewed;
}