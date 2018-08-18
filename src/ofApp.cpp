#include "ofApp.h"

ofApp::Mode ofApp::mode = ofApp::PRODUCTION;

//--------------------------------------------------------------
void ofApp::setup(){

	ofBackground(0);

	// create canvas fbo
	for (int i = 0; i < 2; i++) {
		if (mode == PRODUCTION) {
			screen[i].allocate(Constants::renderSize.x, Constants::renderSize.y, GL_RGBA);
		} else {
			screen[i].allocate(Constants::renderSize.x, Constants::renderSize.y, GL_RGBA);
		}
		screen->getTextureReference().getTextureData().bFlipTexture = true;
	}

	// 3D world
	world = std::make_shared<BaseWorld>(Constants::renderSize.x, Constants::renderSize.y);
	world->addObject<CityObject>();
	world->addObject<CalatravaObject>();
	world->addObject<SDIcosaObject>();
	world->addObject<WarmObject>();

	world2 = std::make_shared<BaseWorld>(Constants::renderSize.x, Constants::renderSize.y);
	world2->addObject<SphereObject>();

	// layer mixer
	mixer = ofPtr<Mixer>(new Mixer());

	mixer->addLayer<PRThreeLayer>()->setWorld(world);
	mixer->addLayer<EdgeThreeLayer>()->setWorld(world);
	mixer->addLayer<FourieLayer>();
	mixer->addLayer<NoiseLayer>();
	mixer->addLayer<TgradLayer>();
	mixer->addLayer<PseudoKnightyanLayer>();
	mixer->addLayer<MandelboxLayer>();
	
	mixer->addLayer<SimpleThreeLayer>()->setWorld(world2);
	
	mixer->setLayerInBin(0, 0, 0);
	mixer->setLayerInBin(0, 1, 0);
	mixer->setLayerInBin(1, 1, 0);
	mixer->setLayerInBin(1, 1, 0);
	
	// post effects
	pfx.init(Constants::renderSize.x, Constants::renderSize.y);
}

//--------------------------------------------------------------
void ofApp::update(){

	DataListener::instance().update();

	mixer->update();

	// if three-layers are all inactive, this process is not necessary
	world->update();
	world2->update();
	
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
	

}

//--------------------------------------------------------------
void ofApp::draw(){
	// output
	ofSetColor(255);
	screen[0].draw(0, 0, Constants::screenSize.x, Constants::screenSize.y);
	screen[1].draw(Constants::screenSize.x, 0, Constants::screenSize.x, Constants::screenSize.y);
}

