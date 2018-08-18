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
		rect.setTexCoord(0, glm::vec2(0, 0));
		rect.setTexCoord(1, glm::vec2(Constants::renderSize.x, 0));
		rect.setTexCoord(2, glm::vec2(0, Constants::renderSize.y));
		rect.setTexCoord(3, Constants::renderSize);

		ofBackground(0);
		
		ofDisableDepthTest();
		
	}

	void update() {}
	
	void draw() {

		ofEnableDepthTest();
		ofEnableBlendMode(OF_BLENDMODE_ALPHA);
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
		ofDisableDepthTest();
		ofDisableBlendMode();

	}

	ofPtr<ofApp> mainApp;

private:
	
	ofRectangle front; ofRectangle rear;
	ofEasyCam cam;
	ofShader shader;

	ofMesh rect;
};