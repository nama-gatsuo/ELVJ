#include "ofApp.h"

ofApp::Mode ofApp::mode = ofApp::SANDBOX;

//--------------------------------------------------------------
void ofApp::setup(){

	ofDisableArbTex();
	for (int i = 0; i < 2; i++) {
		if (mode == PRODUCTION) {
			screen[i].allocate(1920, 1080, GL_RGBA);
		} else {
			screen[i].allocate(960, 540, GL_RGBA);
		}
	}
	ofEnableArbTex();

	// layer 1
	auto l1 = mixer.addLayer<ThreeLayer>();
	l1->setDrawArea(BaseLayer::LEFT);
	l1->addObject<CityObject>();
	l1->setAlpha(1.);

}

//--------------------------------------------------------------
void ofApp::update(){

	mixer.update();

	screen[0].begin();
	ofClear(0);
	mixer.drawLeft();
	screen[0].end();

	screen[1].begin();
	ofClear(0);
	mixer.drawRight();
	screen[1].end();

}

//--------------------------------------------------------------
void ofApp::draw(){
	// output
	screen[0].draw(0, 0);
	screen[1].draw(ofGetWidth() / 2, 0);
}

