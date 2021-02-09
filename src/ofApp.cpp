#include "ofApp.h"

vector2 mouse;
Agent target;
Agent wall;
Agent wall1;
Agent wall2;
Agent wall3;
Agent wall4;
Agent wall5;
//Greedy g;
Runner g;
list<Agent*>agents;
time_t oldTime, deltaTime;

//--------------------------------------------------------------
void ofApp::setup(){
	wall = Agent(vector2(500, 500), 80, 80);
	wall1 = Agent(vector2(100, 600), 80, 80);
	wall2 = Agent(vector2(1200, 100), 80, 80);
	wall3 = Agent(vector2(350, 700), 80, 80);
	wall4 = Agent(vector2(400, 200), 80, 80);
	wall5 = Agent(vector2(1000, 500), 80, 80);
	g = Runner(120, vector2(500, 450), vector2(), vector2(3, 3), 2, 20, 20, 60, 60, vector2(g.position.x, g.position.y), 100.0f);
	target = Agent(vector2(264, 264), vector2(0, 0), vector2(0, 0), 15, 20, 20, 40, 40);
	agents.push_back(&target);
	agents.push_back(&wall);
	agents.push_back(&wall1);
	agents.push_back(&wall2);
	agents.push_back(&wall3);
	agents.push_back(&wall4);
	agents.push_back(&wall5);
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
	wall1.drawObstacle();
	wall2.drawObstacle();
	wall3.drawObstacle();
	wall4.drawObstacle();
	wall5.drawObstacle();
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
