#include "ofApp.h"

vector2 mouse;
Agent target;
Agent wall;
Agent wall1;
Agent wall2;
Agent wall3;
Agent wall4;
Agent wall5;
Greedy g;
Coward cow;
Runner run;
Patrol pat1;
Patrol pat2;
list<Agent*>agents;
list<vector2>path;
list<vector2>path1;
list<vector2>path2;
time_t oldTime, deltaTime;

//--------------------------------------------------------------
void ofApp::setup(){
	wall = Agent(vector2(500, 500), 80, 80);
	wall1 = Agent(vector2(100, 600), 80, 80);
	wall2 = Agent(vector2(1200, 100), 80, 80);
	wall3 = Agent(vector2(350, 700), 80, 80);
	wall4 = Agent(vector2(400, 200), 80, 80);
	wall5 = Agent(vector2(1000, 500), 80, 80);
	run = Runner(120, vector2(60, 100), vector2(), vector2(3, 3), 4, 20, 20, 60, 60, vector2(run.position.x, run.position.y), 100.0f);
	g = Greedy(120, vector2(500, 450), vector2(), vector2(3, 3), 2, 20, 20, 60, 60);
	cow = Coward(120, vector2(900, 100), vector2(), vector2(3, 3), 6, 10, 15, 30, 30);
	pat1 = Patrol(120, vector2(1400, 300), vector2(), vector2(3, 3), 3, 5, 10, 20, 20);
	pat2 = Patrol(120, vector2(1400, 600), vector2(), vector2(3, 3), 3, 5, 10, 20, 20);
	target = Agent(vector2(264, 264), vector2(0, 0), vector2(0, 0), 15, 20, 20, 40, 40);
	
	agents.push_back(&pat1);
	agents.push_back(&target);
	agents.push_back(&cow);
	agents.push_back(&wall);
	agents.push_back(&wall1);
	agents.push_back(&wall2);
	agents.push_back(&wall3);
	agents.push_back(&wall4);
	agents.push_back(&wall5);
	agents.push_back(&g);
	agents.push_back(&run);
	agents.push_back(&pat2);

	path.push_back(vector2(510.0f, 110.0f));
	path.push_back(vector2(300.0f, 400.0f));
	path.push_back(vector2(1500.0f, 450.0f));
	path.push_back(vector2(700.0f, 450.0f));
	path.push_back(vector2(200.0f, 350.0f));
	path.push_back(vector2(900.0f, 520.0f));
	path.push_back(vector2(1200.0f, 660.0f));
	path.push_back(vector2(1550.0f, 820.0f));

	path1.push_back(vector2(200.0f, 300.0f));
	path1.push_back(vector2(900.0f, 300.0f));
	path1.push_back(vector2(1200.0f, 300.0f));
	path1.push_back(vector2(1550.0f, 300.0f));

	path2.push_back(vector2(200.0f, 600.0f));
	path2.push_back(vector2(900.0f, 600.0f));
	path2.push_back(vector2(1200.0f, 600.0f));
	path2.push_back(vector2(1550.0f, 600.0f));

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
	cow.manager(agents, &deltaTime);
	if (deltaTime > 2) {
		oldTime = time(NULL);
	}
	run.manager(agents, path);
	if (deltaTime > 2) {
		oldTime = time(NULL);
	}
	pat1.manager(agents, path1);
	if (deltaTime > 2) {
		oldTime = time(NULL);
	}
	pat2.manager(agents, path2);
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
	g.radar->drawRadar();
	cow.radar->drawRadar();
	run.radar->drawRadar();
	pat1.radar->drawRadar();
	pat2.radar->drawRadar();
	ofSetColor(220, 220, 220);
	ofDrawRectangle(g.position.x, g.position.y, g.width, g.height);
	ofDrawRectangle(run.position.x, run.position.y, run.width, run.height);
	ofDrawCircle(target.position.x, target.position.y, target.radious);
	ofSetColor(20, 120, 220);
	ofDrawRectangle(pat1.position.x, pat1.position.y, pat1.width, pat1.height);
	ofDrawRectangle(pat2.position.x, pat2.position.y, pat2.width, pat2.height);
	ofSetColor(40, 230, 80);
	ofDrawRectangle(cow.position.x, cow.position.y, cow.width, cow.height);
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
