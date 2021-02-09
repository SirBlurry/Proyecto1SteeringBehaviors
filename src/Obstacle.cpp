#include "Obstacle.h"

void Obstacle::setObstacle(vector2 cPoint, float w, float h)
{
	position = cPoint;
	width = w;
	height = h;
	getP0();
	getP1();
	getP2();
	getP3();
	getLenght();
}

float Obstacle::getLenght()
{
	vector2 mag = p0 - p3;
	return lenght = mag.getMagnitud();
}

vector2 Obstacle::getP0()
{
	p0 = position;
	p0.x -= width / 2;
	p0.y -= height / 2;
	return p0;
}

vector2 Obstacle::getP1()
{
	p1 = position;
	p1.x += width / 2;
	p1.y -= height / 2;
	return p1;
}

vector2 Obstacle::getP2()
{
	p2 = position;
	p2.x -= width / 2;
	p2.y += height / 2;
	return p2;
}

vector2 Obstacle::getP3()
{
	p3 = position;
	p3.x += width / 2;
	p3.y += height / 2;
	return p3;
}

void Obstacle::drawObstacle()
{
	ofSetColor(50, 150, 50, 40);
	ofDrawRectangle(position.x, position.y, width, height);
}