#include "Radar.h"

bool Radar::detect(vector2 object)
{
	if (object.getMagnitud() < radius) { return true; }
	return false;
}

void Radar::drawRadar(vector2 owner)
{
	center = owner;
	ofSetColor(200, 60, 80, 60);
	ofDrawCircle(center.x, center.y, radius);
}