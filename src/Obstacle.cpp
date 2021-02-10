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
float Obstacle::getWidth() {
	return width;
}
float Obstacle::getHeight() {
	return height;
}

float Obstacle::getLenght()
{
	vector2 mag = p0 - p3;
	return lenght = mag.getMagnitud();
}

vector2 Obstacle::getMinorDistance(vector2 origin)
{
	vector2 vec = origin - getP0();
	vector2 one = vec;

	vec.normalizar();
	vec = origin - getP1();
	vector2 two = vec;

	vec.normalizar();
	vec = origin - getP2();
	vector2 three = vec;

	vec.normalizar();
	vec = origin - getP3();
	vector2 four = vec;

	vector2 minValue = one;
	list<vector2>min;
	min.push_back(one);
	min.push_back(two);
	min.push_back(three);
	min.push_back(four);

	while (!min.empty())
	{
		if (minValue.getMagnitud() > min.front().getMagnitud()) { minValue = min.front(); }
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