#pragma once

#include "ofMain.h"
#include "Mixer.h"
#include "Layers.h"
#include "Objects.h"
#include "BaseWorld.h"
#include "DataListener.h"
#include "PostEffects.h"

class ofApp : public ofBaseApp {
public:

	// choose run mode
	static enum Mode { SANDBOX, PRODUCTION } mode;

	void setup();
	void update();
	void draw();

	const ofFbo& getFrontFbo() { return screen[0]; }
	const ofFbo& getRearFbo() { return screen[1]; }

private:
	ofPtr<BaseWorld> world;
	ofPtr<Mixer> mixer;
	ofFbo screen[2];
	PostEffects pfx;
};
