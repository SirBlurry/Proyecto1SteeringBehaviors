#include "ofApp.h"
#include "Obstacle.h"

vector2 mouse;
Agent target;
Agent wall;
Greedy g,g2;
list<Agent*> agents , obstacles;
time_t oldTime, deltaTime;
Obstacle obstacle(vector2(500, 500), 100, 300);

//--------------------------------------------------------------
void ofApp::setup(){
	wall = Agent(vector2(500, 500), 100, 300);
	g = Greedy(120, vector2(1400, 400), vector2(), vector2(3, 3), 7, 20, 20, 60, 60);
	target = Agent(vector2(264, 264), vector2(0, 0), vector2(0, 0), 15, 20, 20, 40, 40);
	g2 = Greedy(120, vector2(800, 300), vector2(), vector2(3, 3), 5, 20, 20, 60, 60);
	obstacles.push_back(&wall);
	agents.push_back(&target);
	//agents.push_back();
	agents.push_back(&g2);
	ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {
	deltaTime = time(NULL) - oldTime;
	mouse.x = ofGetMouseX();
	mouse.y = ofGetMouseY();
	target.position = mouse;
	g.manager(agents, &deltaTime, obstacles);
	g2.manager(agents, &deltaTime, obstacles);
	if (deltaTime > 2) {
		oldTime = time(NULL);
	}

}

//--------------------------------------------------------------
void ofApp::draw(){
	wall.drawObstacle();
	obstacle.drawObstacle();
	target.drawObstacle();
	g.drawObstacle();
	g2.drawObstacle();
	ofSetColor(0, 0, 0, 20);
	//ofDrawCircle(g.Displ.x, g.Displ.y, g.perceptionRadious);
	ofSetColor(220, 220, 220);
	ofDrawRectangle(g.position.x, g.position.y, g.width, g.height);
	ofDrawCircle(target.position.x, target.position.y, target.radious);
	g.radar->drawRadar(g.radarCenter());
	g2.radar->drawRadar(g2.radarCenter());
	wall.radar->drawRadar(wall.radarCenter());
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
