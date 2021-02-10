#pragma once
#include"vector2.h"
#include<ofGraphics.h>
#include<list>

using std::list;

class Obstacle
{
public:
	float width = 0.0f;
	float height = 0.0f;
	float lenght = 0.0f;
	vector2 position = vector2(0, 0);
	vector2 p0 = vector2(0, 0);
	vector2 p1 = vector2(0, 0);
	vector2 p2 = vector2(0, 0);
	vector2 p3 = vector2(0, 0);
	vector2 pCenter0 = vector2(0, 0);
	vector2 pCenter1 = vector2(0, 0);
	vector2 pCenter2 = vector2(0, 0);
	vector2 pCenter3 = vector2(0, 0);
	Obstacle() {}
	Obstacle(vector2 cPoint, float w, float h) : position(cPoint), width(w), height(h) 
	{
		getP0();
		getP1();
		getP2();
		getP3();
		getLenght();
	}
	void setObstacle(vector2, float, float);
	float getLenght();
	vector2 getMinorDistance(vector2);
	vector2 getP0();
	vector2 getP1();
	vector2 getP2();
	vector2 getP3();
	vector2 getPCenter0();
	vector2 getPCenter1();
	vector2 getPCenter2();
	vector2 getPCenter3();
	void drawObstacle();
};