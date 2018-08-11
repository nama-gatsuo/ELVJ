#include "ofApp.h"

ofApp::Mode ofApp::mode = ofApp::PRODUCTION;

//--------------------------------------------------------------
void ofApp::setup(){

	// create canvas fbo
	ofDisableArbTex();
	for (int i = 0; i < 2; i++) {
		if (mode == PRODUCTION) {
			screen[i].allocate(1920, 1080, GL_RGBA);
		} else {
			screen[i].allocate(960, 540, GL_RGBA);
		}
	}
	ofEnableArbTex();

	// 3D world
	world = std::make_shared<BaseWorld>(ofGetWidth() / 2, ofGetHeight());
	world->addObject<CityObject>();

	// layer mixer
	mixer = ofPtr<Mixer>(new Mixer());

	// layer 1
	auto l1 = mixer->addLayer<PRThreeLayer>();
	l1->setWorld(world);
	l1->setDrawArea(BaseLayer::LEFT);
	l1->setAlpha(1.);

	// layer 2
	auto l2 = mixer->addLayer<EdgeThreeLayer>();
	l2->setWorld(world);
	l2->setDrawArea(BaseLayer::RIGHT);
	l2->setAlpha(1.);

}

//--------------------------------------------------------------
void ofApp::update(){

	mixer->update();
	world->update();

	screen[0].begin();
	ofClear(0);
	mixer->drawLeft();
	screen[0].end();

	screen[1].begin();
	ofClear(0);
	mixer->drawRight();
	world->getGBufferPointer()->debugDraw();
	screen[1].end();

}

//--------------------------------------------------------------
void ofApp::draw(){
	// output
	screen[0].draw(0, 0);
	screen[1].draw(ofGetWidth() / 2, 0);
}

