#pragma once
#include "BaseLayer.h"
#include "Util.h"

class TwoLayer : public BaseLayer {
public:
	TwoLayer(const glm::ivec2& size, int id) : BaseLayer(size, id) {
		fbo.allocate(size.x, size.y, GL_RGBA);
	}
	
	const ofFbo& getFbo() const { return fbo; }
	void draw() const { fbo.draw(0, 0); }
	virtual void render() = 0;

	virtual void bang(int& id) = 0;

protected:
	ofFbo fbo;
};

class ConstantsLayer : public TwoLayer {
public:
	ConstantsLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {
		
	}

	void render() {
		bangValue.update();

		fbo.begin();
		ofClear(0);

		float v = bangValue.get();
		ofBackgroundGradient(ofFloatColor(v), ofFloatColor(0));
		
		fbo.end();
	}

	void bang(int& id) {
		if (bangFlags[id]) {
			bangValue.addForce();
		}
	}

private:
	Util::PhysicVal bangValue;
};

class FourieLayer : public TwoLayer {
public:
	FourieLayer(const glm::ivec2& size, int id) : TwoLayer(size, id), freq{ 3,5 } {
		shader.load("shader/vfx/passThru.vert", "shader/pfx/FourieTex.frag");
	}

	void render() {
		
		fbo.begin();

		shader.begin();
		shader.setUniform2f("res", glm::vec2(fbo.getWidth(), fbo.getHeight()));
		shader.setUniform1f("time", ofGetElapsedTimef());
		shader.setUniform1iv("fs", freq, 2);

		fbo.draw(0, 0);
		shader.end();

		fbo.end();
	}

	void bang(int& id) {
		if (bangFlags[id]) {
			if (id == 2) {
				freq[0] = int(ofRandom(1, 8));
			} else if (id == 3) {
				freq[1] = int(ofRandom(1, 8));
			}
		}
	
	}

private:
	ofShader shader;
	int freq[2];
};

class NoiseLayer : public TwoLayer {
public:
	NoiseLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {
		shader.load("shader/vfx/passThru.vert", "shader/pfx/NoiseTex.frag");
	}
	void render() {
		bangValue.update();

		fbo.begin();
		ofClear(0);

		shader.begin();
		shader.setUniform1f("noiseRes", 0.01);
		shader.setUniform1f("noiseStrength", bangValue.get());
		shader.setUniform1f("time", ofGetElapsedTimef());

		fbo.draw(0,0);
		shader.end();

		fbo.end();

	}

	void bang(int& id) {
		if (bangFlags[id]) {
			bangValue.to(ofRandom(10.));
		}
	}

private:
	ofShader shader;
	Util::SmoothVal bangValue;
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

	void bang(int& id) {}


};