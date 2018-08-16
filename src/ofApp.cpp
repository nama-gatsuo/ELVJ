#include "ofApp.h"

ofApp::Mode ofApp::mode = ofApp::SANDBOX;

//--------------------------------------------------------------
void ofApp::setup(){

	// create canvas fbo
	//ofDisableArbTex();
	for (int i = 0; i < 2; i++) {
		if (mode == PRODUCTION) {
			screen[i].allocate(Constants::renderSize.x, Constants::renderSize.y, GL_RGBA);
		} else {
			screen[i].allocate(Constants::renderSize.x, Constants::renderSize.y, GL_RGBA);
		}
		screen->getTextureReference().getTextureData().bFlipTexture = true;
	}
	//ofEnableArbTex();

	// 3D world
	world = std::make_shared<BaseWorld>(Constants::renderSize.x, Constants::renderSize.y);
	world->addObject<CityObject>();

	// layer mixer
	mixer = ofPtr<Mixer>(new Mixer());

	// post effects
	pfx.init(Constants::renderSize.x, Constants::renderSize.y);

	// layer 1: photoreal world
	auto l1 = mixer->addLayer<PRThreeLayer>();
	l1->setWorld(world);

	// layer 2: edge world
	auto l2 = mixer->addLayer<EdgeThreeLayer>();
	l2->setWorld(world);
	
	// layer 3
	auto l3 = mixer->addLayer<FourieLayer>();

	// layer 4
	auto l4 = mixer->addLayer<RandomTwoLayer>();

	// layer 5
	auto l5 = mixer->addLayer<TgradLayer>();

	// layer 6
	auto l6 = mixer->addLayer<PseudoKnightyanLayer>();

	// layer 7
	auto l7 = mixer->addLayer<MandelboxLayer>();
	
	mixer->setLayerInBin(0, 0, 0);
	mixer->setLayerInBin(0, 1, 0);
	mixer->setLayerInBin(1, 1, 0);
	mixer->setLayerInBin(1, 1, 0);
	
}

//--------------------------------------------------------------
void ofApp::update(){

	DataListener::instance().update();

	mixer->update();

	// if three-layers are all inactive, this process is not necessary
	world->update();

	ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	screen[1].begin();
	ofClear(0);
	mixer->drawIn(BaseLayer::LEFT);
	//ofDrawBitmapString("fps: " + std::to_string(ofGetFrameRate()), 10, 16);
	screen[1].end();

	screen[0].begin();
	ofClear(0);
	pfx.render(screen[1]);
	pfx.draw(0, 0);
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
	screen[0].draw(0, 0, Constants::screenSize.x, Constants::screenSize.y);
	screen[1].draw(Constants::screenSize.x, 0, Constants::screenSize.x, Constants::screenSize.y);
}

