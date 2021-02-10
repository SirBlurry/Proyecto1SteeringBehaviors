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

vector2 Obstacle::getNearPoint(vector2 origin)
{
	vector2 one = origin - getP0();
	vector2 two = origin - getP1();
	vector2 three = origin - getP2();
	vector2 four = origin - getP3();

	vector2 nearPoint = one;
	list<vector2>min;
	min.push_back(one);
	min.push_back(two);
	min.push_back(three);
	min.push_back(four);
	list<vector2>nearP;
	nearP.push_back(p0);
	nearP.push_back(p1);
	nearP.push_back(p2);
	nearP.push_back(p3);
	while (!min.empty())
	{
		if (nearPoint.getMagnitud() > min.front().getMagnitud()) { nearPoint = nearP.front(); }
		min.pop_front();
		nearP.pop_front();
	}
	if (nearPoint.getMagnitud() == p0.getMagnitud()) { nearPoint -= vector2(50.0f, 50.0f); }
	else if (nearPoint.getMagnitud() == p1.getMagnitud()) { nearPoint += vector2(50.0f, 50.0f); }
	else if (nearPoint.getMagnitud() == p2.getMagnitud())
	{
		nearPoint.x -= 50.0f;
		nearPoint.y += 50.0f;
	}
	else
	{
		nearPoint.x += 50.0f;
		nearPoint.y -= 50.0f;
	}
	return nearPoint;
}

vector2 Obstacle::getNearObstacle(vector2, list<Obstacle*>&)
{
	return vector2();
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

vector2 Obstacle::getTop()
{
	vector2 top = position;
	top.y -= height / 2;
	//top.multiEscalar(0.5f);
	return top;
}

vector2 Obstacle::getBottom()
{
	vector2 bott = position;
	bott.y += height / 2;
	//bott.multiEscalar(0.5f);
	return bott;
}

vector2 Obstacle::getLeft()
{
	vector2 left = position;
	left.x -= width / 2;
	//left.multiEscalar(0.5f);
	return left;
}

vector2 Obstacle::getRight()
{
	vector2 right = position;
	right.x += width / 2;
	//right.multiEscalar(0.5f);
	return right;
}

void Obstacle::drawObstacle()
{
	ofSetColor(50, 150, 50, 40);
	ofDrawRectangle(position.x, position.y, width, height);
}