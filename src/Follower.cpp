#include "Follower.h"

void Follower::manager(Agent*agent, list<Obstacle*>& obstacles)
{
	this->setRadarRadius(50.0f);
	this->radarCenter() = this->position;
	for (Obstacle* ob : obstacles)
	{
		if (this->radar->detect(ob->position, ob->getLenght())
			|| this->radar->detect(ob->getTop(), ob->width / 4)
			|| this->radar->detect(ob->getBottom(), ob->width / 4)
			|| this->radar->detect(ob->getLeft(), ob->height / 4)
			|| this->radar->detect(ob->getRight(), ob->height / 4))
		{
			//Agent::sb->wallAvoidance(this, ob);
			Agent::sb->Hide(this, ob, agent);
			//return;
		}
	}
			sb->Evade(this, agent);
	//sb->seek(this, agent->position);

	Agent::doIt = Agent::limits();
}

bool Follower::perception(Agent* trgt)
{
	vector2 view = velocity;
	view.normalizar();
	view.multiEscalar(120);
	view += position;

	bool viewed = (trgt->position - view).getMagnitud() < perceptionRadious + trgt->radious;
	if (viewed) { this->Displ = view; }
	return viewed;
}