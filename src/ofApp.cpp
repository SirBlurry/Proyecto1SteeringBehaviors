#include "ofApp.h"

vector2 v1(800, 450), v2(0, 0);
Agent a(v1, vector2(0, 0), 5, 20), t;
sBehaviours sb;
//--------------------------------------------------------------
void ofApp::setup() {

}

//--------------------------------------------------------------
void ofApp::update() {
	v2.x = ofGetMouseX();
	v2.y = ofGetMouseY();
	t.position = v2;
	sb.flee(&a, &t);
	//sb.seek(&a, &t);
	//a.position = vector2::suma(a.position, a.velocity);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofDrawRectangle(a.position.x, a.position.y, 64, 64);
	ofDrawCircle(t.position.x, t.position.y, 64);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{ 

}
