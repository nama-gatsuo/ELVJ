#pragma once
#include "BaseLayer.h"

class TwoLayer : public BaseLayer {
public:
	TwoLayer(int w, int h) : BaseLayer(w, h) {
		fbo.allocate(w, h, GL_RGBA);
	}
	
	const ofFbo& getFbo() const { return fbo; }
	void draw() const { fbo.draw(0, 0); }
	virtual void render() = 0;

protected:
	ofFbo fbo;

};

class FourieLayer : public TwoLayer {
public:
	FourieLayer(int w, int h) : TwoLayer(w, h) {
		shader.load("shader/vfx/passThru.vert", "shader/pfx/FourieTex.frag");
	}

	void render() {
		
		fbo.begin();

		shader.begin();
		shader.setUniform2f("res", glm::vec2(fbo.getWidth(), fbo.getHeight()));
		shader.setUniform1f("time", ofGetElapsedTimef());

		fbo.draw(0, 0);
		shader.end();

		fbo.end();
	}

private:
	ofShader shader;
};

class RandomTwoLayer : public TwoLayer {
public:
	RandomTwoLayer(int w, int h) : TwoLayer(w, h) {}

	void render() {
		const int offset = 200;
		
		fbo.begin();
		
		ofClear(0);

		ofSetHexColor(0xffffff);
		ofSetPolyMode(OF_POLY_WINDING_ODD);
		ofBeginShape();
		for (int i = 0; i < 10; i++) {
			ofVertex(ofRandom(-offset, fbo.getWidth() + offset), ofRandom(-offset, fbo.getHeight() + offset));
		}

		ofEndShape();
		fbo.end();
	}

};