#pragma once
#include "vector2.h"
#include<ofGraphics.h>

class Obstacle
{
public:
	float width = 0.0f;
	float height = 0.0f;
	float lenght = 0.0f;
	vector2 distanceX = vector2(0, 0);
	vector2 distanceY = vector2(0, 0);
	vector2 position = vector2(0, 0);
	Obstacle() {}
	Obstacle(vector2 cPoint, float w, float h) : position(cPoint), width(w), height(h) 
	{
		getDistanceX();
		getDistanceY();
		getLenght();
	}
	void setObstacle(vector2, float, float);
	float getLenght();
	vector2 getDistanceX();
	vector2 getDistanceY();
	void drawObstacle();
};