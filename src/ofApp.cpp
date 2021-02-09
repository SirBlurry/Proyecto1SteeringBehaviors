#include "ofApp.h"
#include "Obstacle.h"

vector2 mouse;
Agent target;
Agent wall;
Greedy g;
list<Agent*> agents;
time_t oldTime, deltaTime;
Obstacle obstacle(vector2(500, 500), 100, 300);

//--------------------------------------------------------------
void ofApp::setup(){
	wall = Agent(vector2(500, 500), 100, 300);
	g = Greedy(120, vector2(1400, 400), vector2(), vector2(3, 3), 4, 20, 20, 60, 60);
	target = Agent(vector2(264, 264), vector2(0, 0), vector2(0, 0), 15, 20, 20, 40, 40);
	agents.push_back(&wall);
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
	wall.drawObstacle();
	target.drawObstacle();
	g.drawObstacle();
	ofSetColor(0, 0, 0, 20);
	ofDrawCircle(g.Displ.x, g.Displ.y, g.perceptionRadious);
	ofSetColor(220, 220, 220);
	ofDrawRectangle(g.position.x, g.position.y, g.width, g.height);
	ofDrawCircle(target.position.x, target.position.y, target.radious);
	g.radar->drawRadar(g.radarCenter());
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
