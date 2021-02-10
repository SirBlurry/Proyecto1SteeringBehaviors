#include "Patrol.h"

void Patrol::manager(list<Agent*>& agents, list<vector2>& path, list<Obstacle*>& obstacles)
{
	this->setRadarRadius(35.0f);
	this->radarCenter() = this->velocity;
	this->radarCenter().normalizar();
	this->radarCenter().multiEscalar(35.0f);
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