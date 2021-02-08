#pragma once
//#include "ofMain.h"
#include <ofAppRunner.h>
#include "vector2.h"
#include "Radar.h"
#include <list>
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using std::list; using std::cout; using std::endl;

class Agent {
	private:
		//class sBehaviours; // fordward declaration
		class sBehaviours {
			private:
				bool canChange = true;
				vector2 displacement = vector2(0,0);
			public:
				//class Agent;
				sBehaviours() {
					displacement = vector2(rand() % 101 - 50, rand() % 101 - 50);
				}
				void wander(Agent*, float, time_t*);
				void arrival(Agent*, Agent*);
				void seek(Agent*, Agent*);
				void flee(Agent*, Agent*);
		};
	protected:
		bool doIt = false;
		sBehaviours* sb = new sBehaviours();
		bool limits();
	public:
		Radar* radar = new Radar();
		vector2 Displ = vector2(0, 0);
		float maxVel = 0, mass = 0, radious = 0;
		vector2 position = vector2(0,0);
		vector2 velocity = vector2(0,0);
		vector2 maxForce = vector2(0, 0);
		Agent() {}
		Agent(vector2, vector2, float, float);
		Agent(vector2, vector2, vector2, float, float, float);
};