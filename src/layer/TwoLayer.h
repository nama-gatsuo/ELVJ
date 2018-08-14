#pragma once
#include "BaseLayer.h"

class TwoLayer : public BaseLayer {
public:
	TwoLayer(const glm::ivec2& size, int id) : BaseLayer(size, id) {
		fbo.allocate(size.x, size.y, GL_RGBA);
	}
	
	const ofFbo& getFbo() const { return fbo; }
	void draw() const { fbo.draw(0, 0); }
	virtual void render() = 0;

	void bang(int& id) {}

protected:
	ofFbo fbo;
};

class ConstantsLayer : public TwoLayer {
public:
	ConstantsLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {
		
	}

	void render() {
		fbo.begin();
		ofClear(0);
		fbo.end();
	}

private:


};

class FourieLayer : public TwoLayer {
public:
	FourieLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {
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
	RandomTwoLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {}

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