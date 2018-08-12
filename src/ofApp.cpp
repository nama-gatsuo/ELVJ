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
	world = std::make_shared<BaseWorld>(Constants::renderSize.x, Constants::renderSize.y);
	world->addObject<CityObject>();

	// layer mixer
	mixer = ofPtr<Mixer>(new Mixer());

	// layer 1
	auto l1 = mixer->addLayer<PRThreeLayer>();
	l1->setWorld(world);
	l1->toggleDrawIn(BaseLayer::LEFT);
	l1->setAlpha(1.);

	// layer 2
	auto l2 = mixer->addLayer<EdgeThreeLayer>();
	l2->setWorld(world);
	l2->toggleDrawIn(BaseLayer::LEFT);
	l2->setAlpha(1.);

	// layer 3
	auto l3 = mixer->addLayer<RandomTwoLayer>();
	//l3->toggleDrawIn(BaseLayer::LEFT);
	l3->toggleDrawIn(BaseLayer::RIGHT);
	l3->setAlpha(1.);

	// layer 3
	auto l4 = mixer->addLayer<FourieLayer>();
	l4->toggleDrawIn(BaseLayer::LEFT);
	//l4->toggleDrawIn(BaseLayer::RIGHT);
	l4->setAlpha(1.);

	Mixer::State s;
	s.mode = Mixer::Mode::TWO_CHAN_MIX;
	s.mixLayer = 3;
	s.mix[0] = 1;
	s.mix[1] = 0;
	mixer->setMixerState(BaseLayer::LEFT, s);

}

//--------------------------------------------------------------
void ofApp::update(){

	DataListener::instance().update();

	mixer->update();

	// if three-layers are all inactive, this process is not necessary
	world->update();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	screen[0].begin();
	ofClear(0);
	mixer->drawIn(BaseLayer::LEFT);
	//ofDrawBitmapString("fps: " + std::to_string(ofGetFrameRate()), 10, 16);
	screen[0].end();

	screen[1].begin();
	ofClear(0);
	mixer->drawIn(BaseLayer::RIGHT);
	screen[1].end();
	ofDisableBlendMode();

}

//--------------------------------------------------------------
void ofApp::draw(){
	// output
	screen[0].draw(0, 0);
	//screen[1].draw(ofGetWidth() / 2, 0);
}

