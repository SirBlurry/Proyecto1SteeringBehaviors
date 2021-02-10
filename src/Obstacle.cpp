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
	getPCenter0();
	getPCenter1();
	getPCenter2();
	getPCenter3();
	getLenght();
}

float Obstacle::getLenght()
{
	vector2 mag = p0 - p3;
	mag.normalizar();
	mag.generarMagnitud();
	return lenght = mag.getMagnitud();
}

vector2 Obstacle::getMinorDistance(vector2 origin)
{
	vector2 one = origin - getP0();
	vector2 two = origin - getP1();
	vector2 three = origin - getP2();
	vector2 four = origin - getP3();
	vector2 oneCenter = origin - getPCenter0();
	vector2 twoCenter = origin - getPCenter1();
	vector2 threeCenter = origin - getPCenter2();
	vector2 fourCenter = origin - getPCenter3();

	vector2 minValue = one;
	list<vector2>min;
	min.push_back(one);
	min.push_back(two);
	min.push_back(three);
	min.push_back(four);
	min.push_back(oneCenter);
	min.push_back(twoCenter);
	min.push_back(threeCenter);
	min.push_back(fourCenter);

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

vector2 Obstacle::getPCenter0()
{
	pCenter0 = position;
	pCenter0.y -= height;
	return pCenter0;
}

vector2 Obstacle::getPCenter1()
{
	pCenter1 = position;
	pCenter1.y += width;
	return pCenter1;
}

vector2 Obstacle::getPCenter2()
{
	pCenter2 = position;
	pCenter2.y += height;
	return pCenter2;
}

vector2 Obstacle::getPCenter3()
{
	pCenter3 = position;
	pCenter3.y -= width;
	return pCenter3;
}

void Obstacle::drawObstacle()
{
	ofSetColor(50, 150, 50, 40);
	ofDrawRectangle(position.x, position.y, width, height);
}