#include "Runner.h"

void Runner::manager(list<Agent*>& agents, list<vector2>& path, list<Obstacle*>& obstacles)
{
	this->setRadarRadius(50.0f);
	this->radarCenter() = this->velocity;
	this->radarCenter().normalizar();
	this->radarCenter().multiEscalar(80.0f);
	this->radarCenter() += this->position;
	for (Obstacle* ob : obstacles)
	{
		if (this->radar->detect(ob->position, ob->getLenght())
			|| this->radar->detect(ob->getTop(), ob->width / 4)
			|| this->radar->detect(ob->getBottom(), ob->width / 4)
			|| this->radar->detect(ob->getLeft(), ob->height / 4)
			|| this->radar->detect(ob->getRight(), ob->height / 4))
		{
			Agent::sb->wallAvoidance(this, ob);
			return;
		}
		for (Agent* ag : agents)
		{
			if ((ag != this) && (this->radar->detect(ag->position, ag->lenght)
				|| this->radar->detect(ag->getP0(), ag->lenght)
				|| this->radar->detect(ag->getP1(), ag->lenght)
				|| this->radar->detect(ag->getP2(), ag->lenght)
				|| this->radar->detect(ag->getP3(), ag->lenght))/*perception(ag)*/)
			{
				Agent::sb->obstacleAvoidance(this, ag);
				return;
			}
		}
	}
	//sb->pathFollowing(this, &path);
	sb->interpose(this, agents.front(), agents.back());
	Agent::doIt = Agent::limits();
}

bool Runner::perception(Agent* trgt)
{
	vector2 view = velocity;
	view.normalizar();
	view.multiEscalar(120);
	view += position;

	bool viewed = (trgt->position - view).getMagnitud() < perceptionRadious + trgt->radious;
	if (viewed) { this->Displ = view; }
	return viewed;
}