#include "Obstacle.h"

void Obstacle::setObstacle(vector2 cPoint, float w, float h)
{
	position = cPoint;
	width = w;
	height = h;
	getDistanceX();
	getDistanceY();
	getLenght();
}

float Obstacle::getLenght()
{
	vector2 mag = distanceX - distanceY;
	return lenght = mag.getMagnitud();
}

vector2 Obstacle::getDistanceX()
{
	distanceX = position;
	distanceX.x -= width / 2;
	distanceX.y -= height / 2;
	return distanceX;
}

vector2 Obstacle::getDistanceY()
{
	distanceY = position;
	distanceY.x += width / 2;
	distanceY.y += height / 2;
	return distanceY;
}

void Obstacle::drawObstacle()
{
	ofSetColor(50, 150, 50, 40);
	ofDrawRectangle(position.x, position.y, width, height);
}