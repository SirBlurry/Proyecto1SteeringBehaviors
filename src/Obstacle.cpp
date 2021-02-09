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

float Obstacle::getminorDistance(vector2 origin)
{
	unsigned count = 3;
	vector2 vec = origin - getP0();
	vec.generarMagnitud();
	float one = vec.getMagnitud();

	vec.normalizar();
	vec = origin - getP1();
	vec.generarMagnitud();
	float two = vec.getMagnitud();

	vec.normalizar();
	vec = origin - getP2();
	vec.generarMagnitud();
	float three = vec.getMagnitud();

	vec.normalizar();
	vec = origin - getP3();
	vec.generarMagnitud();
	float four = vec.getMagnitud();

	float minValue = one;
	list<float>min;
	min.push_back(one);
	min.push_back(two);
	min.push_back(three);
	min.push_back(four);

	while (!min.empty())
	{
		if (minValue > min.front()) { minValue = min.front(); }
		min.pop_front();
	}
	return minValue;
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