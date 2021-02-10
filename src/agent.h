#pragma once
#include <ofAppRunner.h>
#include "Radar.h"
#include "Obstacle.h"
//#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using std::cout; using std::endl;
using std::vector;

class Agent : public Obstacle
{
	private:
		//class sBehaviours; // fordward declaration
		class sBehaviours 
		{
			private:
				bool canChange = true;
				vector2 displacement = vector2(0,0);
			public:
				//class Agent;
				sBehaviours() {
					displacement = vector2(rand() % 101 - 50, rand() % 101 - 50);
				}
				void wander(Agent*, float, time_t*);
				void arrival(Agent*, vector2, float);
				void interpose(Agent*, Agent*, Agent*);
				void seek(Agent*, vector2);
				void flee(Agent*, Agent*);
				void obstacleAvoidance(Agent*, Obstacle*);
				void wallAvoidance(Agent*, Obstacle*);
				void pathFollowing(Agent*, list<vector2>*);
				void OffsetPursuit(Agent*, float, Agent*);
				void Hide(Agent*, list<Obstacle*>&, Agent*);
				void Evade(Agent*, Agent*);
				void Pursuit(Agent*, Agent*);
		};
	protected:
		bool doIt = false;
		sBehaviours* sb = new sBehaviours();
		bool limits();
	public:
		Radar* radar = new Radar();
		vector2 Displ = vector2(0, 0);
		float maxVel = 0, mass = 0, radious = 0;
		vector2 velocity = vector2(0,0);
		vector2 maxForce = vector2(0, 0);
		Agent() {}
		Agent(vector2, float, float);
		Agent(vector2, vector2, float, float, float, float);
		Agent(vector2, vector2, vector2, float, float, float, float, float);
		Agent(vector2, vector2, float, float,float, float, vector2, float);
		Agent(vector2, vector2, vector2, float, float, float, float, float, vector2, float);
		vector2& radarCenter();
		void setRadarRadius(float);
		float getRadarRadius();
};