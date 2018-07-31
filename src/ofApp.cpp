#include "ofApp.h"

ofApp::Mode ofApp::mode = ofApp::SANDBOX;

//--------------------------------------------------------------
void ofApp::setup(){

	for (int i = 0; i < 2; i++) {
		if (mode == PRODUCTION) {
			screen[i].allocate(1920, 1080, GL_RGBA);
		} else {
			screen[i].allocate(960, 540, GL_RGBA);
		}
	}



}

//--------------------------------------------------------------
void ofApp::update(){
	screen[0].begin();
	ofClear(0);
	ofDrawRectangle(50, 50, 800, 300);
	screen[0].end();

	screen[1].begin();
	ofClear(0);
	ofDrawCircle(200, 200, 100, 100);
	screen[1].end();
}

//--------------------------------------------------------------
void ofApp::draw(){
	// output
	screen[0].draw(0, 0);
	screen[1].draw(ofGetWidth() / 2 + 1, 0);
}

