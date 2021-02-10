#include "Radar.h"

bool Radar::detect(vector2 object, float objRadius)
{
	if ((object - center).getMagnitud() < radius + objRadius) { return true; }
	return false;
}

void Radar::drawRadar()
{
	ofSetColor(200, 60, 80, 60);
	ofDrawCircle(center.x, center.y, radius);
}