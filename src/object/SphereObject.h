#pragma once
#include "ofMain.h"
#include "BaseObject.h"
#include "Util.h"

class SParams {
public:
	void init() {

		rInit.to(ofRandom(50, 600));
		rStep.to(ofRandom(0.1, 3.0));
		sStep.to(ofRandom(-0.05, 0.05));
		tStep.to(ofRandom(-0.05, 0.05));

	}
	void update() {
		rInit.update();
		rStep.update();
		sStep.update();
		tStep.update();
	}
	void randomize() {
		if (ofRandom(1.0) < 0.2) {
			rStep.to(ofRandom(-0.1, 0.1));
		} else {
			rStep.to(ofRandom(-0.5, 0.5));
		}

		rInit.to(ofRandom(10, 300));

		if (ofRandom(1.0) < 0.2) {
			sStep.to(ofRandom(-0.1, 0.1));
		} else {
			sStep.to(ofRandom(-0.03, 0.03));
		}

		if (ofRandom(1.0) < 0.2) {
			tStep.to(ofRandom(-0.01, 0.01));
		} else {
			tStep.to(ofRandom(-0.03, 0.03));
		}

	}

	Util::SmoothVal rInit;
	Util::SmoothVal rStep;
	Util::SmoothVal sStep;
	Util::SmoothVal tStep;
};

class SphereObject : public BaseObject {
public:
	SphereObject(int id) : BaseObject(id) {
		mesh.setMode(OF_PRIMITIVE_POINTS);
		for (int s = 0; s < sSize; s++) {
			for (int t = 0; t < tSize; t++) {
				for (int r = 0; r < rSize; r++) {

					mesh.addVertex(ofVec3f(0, 0, 0));
					mesh.addTexCoord(ofVec2f(t*rSize + r, s));
					mesh.addColor(ofFloatColor(0.3 + ofRandom(-0.1, 0.1), 0.3 + ofRandom(-0.1, 0.1), 0.3, 0.1));

				}
			}
		}

		shader.load("shader/scene/spiral");
		shader.begin();
		shader.setUniform1f("rSize", rSize);
		shader.setUniform1f("sSize", sSize);
		shader.setUniform1f("tSize", tSize);
		shader.end();

		for (int i = 0; i < spNum; i++) {
			ps[i].init();
		}
	}
	
	void update() {
		for (int i = 0; i < spNum; i++) {
			ps[i].update();
		}
	}
	void draw(float lds) {

		ofDisableDepthTest();
		ofEnableBlendMode(OF_BLENDMODE_ADD);
		glEnable(GL_POINT_SPRITE);
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

		for (int i = 0; i < spNum; i++) {

			ofPushMatrix();
			ofRotateX(-i * 36);
			ofRotateZ(i * 36);

			shader.begin();
			shader.setUniform1f("rInit", ps[i].rInit.get());
			shader.setUniform1f("rStep", ps[i].rStep.get());
			shader.setUniform1f("sStep", ps[i].sStep.get());
			shader.setUniform1f("tStep", ps[i].tStep.get());

			mesh.draw();

			shader.end();
			ofPopMatrix();
		}
		ofDisableBlendMode();
		ofEnableDepthTest();
	}
	void bang(int& id) {
		if (bangFlags[id]) {
			for (int i = 0; i < spNum; i++) {
				ps[i].randomize();
			}
		}
	}
	

private:
	ofShader shader;
	ofVboMesh mesh;

	int rSize = 100;
	int tSize = 24;
	int sSize = 12;

	int spNum = 10;
	SParams ps[10];
};