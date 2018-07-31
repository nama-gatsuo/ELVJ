#pragma once

#include "ofMain.h"

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

	ofFbo screen[2];
};
