#pragma once
#include "ofBaseApp.h"
#include "ofTypes.h"
#include "ofEasyCam.h"
#include "ofApp.h"

class SimulatorApp : public ofBaseApp {
public:

	void setup() {
		cam.setDistance(30);
		rect = ofMesh::plane(16, 9, 2, 2);
		
		ofBackground(0);
		
		ofDisableDepthTest();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	}

	void update() {}
	
	void draw() {
		
		cam.begin();

		mainApp->getRearFbo().getTextureReference().bind();
		for (int i = 0; i < 3; i++) {
			ofPushMatrix();
			ofTranslate(16 * (i - 1), 0, 10);
			rect.draw(OF_MESH_FILL);
			ofPopMatrix();
		}
		mainApp->getRearFbo().getTextureReference().unbind();
		
		mainApp->getFrontFbo().getTextureReference(0).bind();
		for (int i = 0; i < 3; i++) {
			ofPushMatrix();
			ofTranslate(16 * (i - 1), 0, -10);
			rect.draw(OF_MESH_FILL);
			ofPopMatrix();
		}
		mainApp->getFrontFbo().getTextureReference(0).unbind();

		cam.end();
		
	}

	ofPtr<ofApp> mainApp;

private:
	
	ofRectangle front; ofRectangle rear;
	ofEasyCam cam;
	ofShader shader;

	ofMesh rect;
};