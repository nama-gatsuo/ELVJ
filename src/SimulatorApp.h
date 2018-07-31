#pragma once
#include "ofBaseApp.h"
#include "ofTypes.h"
#include "ofEasyCam.h"
#include "ofApp.h"

class SimulatorApp : public ofBaseApp {
public:

	void setup() {
		
		rect = ofMesh::plane(16, 9, 1, 1);
		
	}

	void update() {}
	
	void draw() {
		ofEnableAlphaBlending();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
		
		cam.begin();
		mainApp->getRearFbo().getTexture().bind();
		for (int i = 0; i < 3; i++) {
			ofPushMatrix();
			ofTranslate(16 * (i - 1), 0, 10);
			ofRotate(90, 1, 0, 0);

			rect.draw();
			ofPopMatrix();
		}
		mainApp->getRearFbo().getTexture().unbind();
		
		mainApp->getFrontFbo().getTexture().bind();
		for (int i = 0; i < 3; i++) {
			ofPushMatrix();
			ofTranslate(16 * (i - 1), -10);
			ofRotate(90, 1, 0, 0);

			rect.draw();
			ofPopMatrix();
		}
		mainApp->getFrontFbo().getTexture().unbind();

		ofDisableBlendMode();
		ofDisableAlphaBlending();
		
		cam.end();
	}

	ofPtr<ofApp> mainApp;

private:
	
	ofRectangle front; ofRectangle rear;
	ofEasyCam cam;

	ofVboMesh rect;
};