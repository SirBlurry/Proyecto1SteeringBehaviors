#include "Radar.h"

bool Radar::detect(vector2 object, float objRadius)
{
	if ((center - object).getMagnitud() < radius + objRadius) { return true; }
	return false;
}

void Radar::drawRadar()
{
	ofSetColor(200, 60, 80, 60);
	ofDrawCircle(center.x, center.y, radius);
}
bool Radar::CollisionObj(Obstacle* obstacle) {
	if (center.x > obstacle->getP0().x && center.x < obstacle->getP3().x && center.y > obstacle->getP0().y && center.y < obstacle->getP3().y) { return true; }
	return false;
}