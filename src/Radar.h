#pragma once
#include"vector2.h"
#include<list>
#include<ofGraphics.h>
#include "Obstacle.h"

using std::list;

class Radar
{
private:
public:
	float radius = 0.0f;
	vector2 center = vector2(0, 0);
	list<vector2*>objects;
	list<float>lenghts;
	Radar() {}
	Radar(float rad) : radius(rad) {}
	Radar(vector2 owner, float rad) : center(owner), radius(rad) {}
	bool detect(vector2, float);
	void drawRadar();
	bool CollisionObj(Obstacle* obstacle);
};