#pragma once
#include"vector2.h"
#include<list>
#include<ofGraphics.h>

using std::list;

class Radar
{
public:
	float radius = 0.0f;
	vector2 center = vector2(0, 0);
	list<vector2*> objects;
	Radar() {}
	Radar(float rad) : radius(rad) {}
	Radar(vector2 owner, float rad) : center(owner), radius(rad) {}
	bool detect(vector2);
	void drawRadar(vector2);
};