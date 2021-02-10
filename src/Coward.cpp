#include "Coward.h"

void Coward::manager(list<Agent*>& agents, time_t* deltaTime)
{
	this->setRadarRadius(60.0f);
	this->radarCenter() = this->velocity;
	this->radarCenter().normalizar();
	this->radarCenter().multiEscalar(40.0f);
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
			Agent::sb->flee(this, ag);
			return;
		}
	}
	sb->wander(this, 60.0f, deltaTime);
	Agent::doIt = Agent::limits();
}

bool Coward::perception(Agent* trgt)
{
	vector2 view = velocity;
	view.normalizar();
	view.multiEscalar(120);
	view += position;

	bool viewed = (trgt->position - view).getMagnitud() < perceptionRadious + trgt->radious;
	if (viewed) { this->Displ = view; }
	return viewed;
}