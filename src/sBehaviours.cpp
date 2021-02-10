//#include "sBehaviours.h"
#include "agent.h"

void Agent::sBehaviours::wander(Agent* self, float vista, time_t* deltaTime) {
	int rango = 1000;
	self->setRadarRadius(vista);
	self->radarCenter() = self->velocity;
	self->radarCenter().normalizar();
	self->radarCenter().multiEscalar(vista);
	self->radarCenter() += self->position;

	/*vector2 guide = self->velocity;
	guide.normalizar();
	guide.multiEscalar(vista);
	guide += self->position;*/
	if (*deltaTime == 1) canChange = true;
	if ((*deltaTime == 0 && canChange) || self->doIt) {
		displacement = vector2((rand() % (rango * 2 + 1)) - rango, (rand() % (rango * 2 + 1)) - rango);
		//cout << displacement.x << ", " << displacement.y << ", " << *deltaTime << endl;
		canChange = false;
		if(self->doIt) self->doIt = false;
	}
	seek(self, displacement);
	//self->Displ = self->radarCenter();
	//vector2 steering = self->radarCenter() + displacement;
	///*self->Displ = guide;
	//vector2 steering = guide + displacement;*/
	////cout << "steer: " << steering.x << ", " << steering.y << endl;
	//steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	//steering.dividirEscalar(self->mass);

	//self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	//self->position += self->velocity;
}

void Agent::sBehaviours::arrival(Agent* owner, vector2 target, float slowArea)
{
	vector2 firstCenter = owner->radarCenter();
	owner->setRadarRadius(slowArea);
	vector2 desired_vel = target - owner->position;
	vector2 slowLimit = target - owner->position;
	desired_vel.normalizar();
	if (owner->radar->detect(target, slowArea))
	{
		owner->radarCenter() = target;
		desired_vel.multiEscalar(owner->maxVel * (slowLimit.getMagnitud() / slowArea));
		if (!owner->radar->detect(owner->position, slowArea))
		{
			owner->radarCenter() = firstCenter;
			desired_vel.multiEscalar(owner->maxVel);
		}
	}
	vector2 steering = vector2::resta(desired_vel, owner->velocity);
	steering = vector2::truncar(steering, owner->maxForce.getMagnitud());
	steering.dividirEscalar(owner->mass);
	owner->velocity = vector2::truncar((steering + owner->velocity), owner->maxVel);
	owner->position += owner->velocity;
}

void Agent::sBehaviours::interpose(Agent* self, Agent* target1, Agent* target2)
{
	vector2 middle = target1->position + target2->position;
	middle.dividirEscalar(2.0f);
	vector2 time = self->position - middle;
	time.dividirEscalar(self->maxVel);
	float timeToIntercept = time.getMagnitud();
	if (self->radar->detect(time, self->getRadarRadius()))
	{
		arrival(self, middle, middle.getMagnitud());
	}
	else
	{
		seek(self, middle);
	}
	vector2 firstPos = target1->position + target1->velocity;
	firstPos.multiEscalar(timeToIntercept);
	vector2 secondPos = target2->position + target2->velocity;
	secondPos.multiEscalar(timeToIntercept);
	middle = firstPos - secondPos;
	middle.dividirEscalar(2.0f);
}

void Agent::sBehaviours::seek(Agent* self, vector2 target)
{
	vector2 v = vector2(0, 0);
	vector2 desired_vel = target - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);

	vector2 steering = desired_vel - self->velocity;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::obstacleAvoidance(Agent* self, vector2 destiny, list<Agent*>& agents)
{
	vector2 avoid;
	for (Agent* ag : agents)
	{
		/*if (self->radar->detect(ag->position, ag->width) || self->radar->detect(ag->position, ag->height))*/
		if (self->radar->detect(ag->position, ag->getLenght()))
		{
			avoid = self->radarCenter() - ag->getMinorDistance(self->velocity);
			avoid.normalizar();
			avoid.multiEscalar(self->maxVel);
		}
		else
		{
			avoid.multiEscalar(0.0f);
		}
	}
	vector2 steering = self->velocity + avoid;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position += self->velocity;
}

void Agent::sBehaviours::pathFollowing(Agent* self, list<vector2>* nodes)
{
	if (!nodes->empty())
	{
		vector2 current = nodes->front();
		vector2 distance = current - self->position;
		if (self->radar->detect(current, 5.0f))
		{
			nodes->pop_front();
			nodes->push_back(current);
		}
		seek(self, current);
	}
}

void Agent::sBehaviours::flee(Agent* self, Agent* target)
{
	vector2 desired_vel = target->position - self->position;
	desired_vel.normalizar();
	desired_vel.multiEscalar(self->maxVel);

	vector2 steering = desired_vel - self->velocity;
	steering = vector2::truncar(steering, self->maxForce.getMagnitud());
	steering.dividirEscalar(self->mass);

	self->velocity = vector2::truncar((steering + self->velocity), self->maxVel);
	self->position -= self->velocity;
}