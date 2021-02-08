#include "ofApp.h"

vector2 mouse;
Agent target;
Greedy g;
list<Agent*> agents;
time_t oldTime, deltaTime;

//--------------------------------------------------------------
void ofApp::setup(){
	g = Greedy(400, vector2(264, 264), vector2(), vector2(3, 3), 4, 20, 20);
	target = Agent(vector2(264, 264), vector2(0, 0), vector2(0, 0), 15, 20, 20);
	agents.push_back(&target);
	agents.push_back(&g);
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update(){
	deltaTime = time(NULL) - oldTime;
	mouse.x = ofGetMouseX();
	mouse.y = ofGetMouseY();
	target.position = mouse;
	g.manager(agents, &deltaTime);
	if (deltaTime > 2) {
		oldTime = time(NULL);
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(0, 0, 0, 40);
	ofDrawCircle(g.Displ.x, g.Displ.y, g.perceptionRadious);
	ofSetColor(220, 220, 220);
	ofDrawRectangle(g.position.x, g.position.y, 64, 64);
	ofDrawCircle(target.position.x, target.position.y, target.radious);
	g.radar->drawRadar(target.position);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
