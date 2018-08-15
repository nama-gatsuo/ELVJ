#pragma once
#include "TwoLayer.h"
#include "ofGraphics.h"
#include "ofShader.h"
#include "ofUtils.h"
#include "ofMath.h"
#include "Util.h"

class TgradLayer : public TwoLayer {
public:
	TgradLayer(const glm::ivec2& size, int id) : TwoLayer(size, id), p0(glm::vec3(0.0, 1.59, -1.0)) {
		shader.load("shader/vfx/passThru.vert", "shader/scene/raymarch/Tgrad.frag");
	}

	void render() {
		p0.update();

		fbo.begin();
		ofClear(0.);

		shader.begin();

		shader.setUniform2f("res", Constants::renderSize.x, Constants::renderSize.y);
		shader.setUniform3f("cp", glm::vec3(sin(ofGetElapsedTimef()) * 0.5, 0., cos(ofGetElapsedTimef() * 0.5)));
		shader.setUniform4f("color", ofFloatColor(.1));
		shader.setUniform1f("equiFactor", ofClamp((sin(ofGetElapsedTimef())) * 4., 0., 1.));

		shader.setUniform1f("minr", ofClamp(sin(ofGetElapsedTimef()), 0.2, 0.5));
		shader.setUniform1f("maxr", ofClamp(cos(ofGetElapsedTimef()) + 1., 0.75, 1.25));
		shader.setUniform1f("minc", ofClamp(-sin(ofGetElapsedTimef() * 0.1) * 0.2 - 9., -1.0, -0.8));
		shader.setUniform1f("maxc", ofClamp(-cos(ofGetElapsedTimef() * 0.3) + 0.9, 0.8, 1.));
		shader.setUniform1f("scale", ofClamp(sin(ofGetElapsedTimef() * 0.2) + 0.3 - 3.1, -3.2, -3.));
		shader.setUniform3f("offset", glm::vec3(1.2, 49.0, 1.4));
		shader.setUniform3f("p0", p0.get());
		
		fbo.draw(0, 0);

		shader.end();
		fbo.end();
	}

	void bang(int& id) {
		if (bangFlags[id]) {
			float coin = ofRandom(1.);
			if (coin < 0.2) {
				p0.toX(ofRandom(0.5, 1.));
			} else if (coin < 0.4) {
				p0.toY(ofRandom(0.5, 1.));
			} else if (coin < .6) {
				p0.toX(ofRandom(0.5, 1.));
			}
		}
	}

private:
	ofShader shader;
	Util::SmoothPoint p0;
};

class MandelboxLayer : public TwoLayer {
public:
	MandelboxLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {
		shader.load("shader/vfx/passThru.vert", "shader/scene/raymarch/Mandelbox.frag");
	}

	void render() {
		offset.update();

		fbo.begin();
		ofClear(0.);

		shader.begin();
		shader.setUniform2f("res", Constants::renderSize.x, Constants::renderSize.y);
		shader.setUniform3f("cp", glm::vec3(sin(ofGetElapsedTimef()) * 0.1, 1., cos(ofGetElapsedTimef() * 0.1)));
		shader.setUniform4f("color", ofFloatColor(.1));
		shader.setUniform1f("equiFactor", ofClamp((sin(ofGetElapsedTimef())) * 2., 0., 1.));

		shader.setUniform1f("minRadius2", 0.1);
		shader.setUniform1f("fixedRadius2", 0.9);
		shader.setUniform1f("foldingLimit", 0.9);
		shader.setUniform1f("scale", -3.12);
		shader.setUniform3f("offset", offset.get());
		shader.setUniform1f("rep", 0.);

		fbo.draw(0, 0);

		shader.end();
		fbo.end();
	}
	void bang(int& id) {
		if (bangFlags[id]) {
			float coin = ofRandom(1.);
			if (coin < 0.3) {
				offset.toX(ofRandom(-4., 4.));
			} else if (coin < 0.6) {
				offset.toY(ofRandom(-4., 4.));
			} else if (coin < 0.9) {
				offset.toZ(ofRandom(-4., 4.));
			} 
		}
	}
private:
	ofShader shader;
	Util::SmoothPoint offset;
	
};

class PseudoKnightyanLayer : public TwoLayer {
public:
	PseudoKnightyanLayer(const glm::ivec2& size, int id) :
		TwoLayer(size, id), kFactor(0.70968), offset(0.92784),
		csize(glm::vec3(0.63248, 0.78632, 0.775)) {
		
		shader.load("shader/vfx/passThru.vert", "shader/scene/raymarch/PseudoKnightyan.frag");
	}

	void render() {

		kFactor.update();
		offset.update();
		csize.update();

		fbo.begin();
		ofClear(0.);

		shader.begin();
		shader.setUniform2f("res", Constants::renderSize.x, Constants::renderSize.y);
		shader.setUniform3f("cp", glm::vec3(sin(ofGetElapsedTimef()) * 0.5, 0., cos(ofGetElapsedTimef() * 0.5)));
		shader.setUniform4f("color", ofFloatColor(.1));
		shader.setUniform1f("equiFactor", ofClamp((sin(ofGetElapsedTimef())) * 2., 0., 1.));

		shader.setUniform1f("kFactor", kFactor.get());
		shader.setUniform1f("offset", offset.get());
		shader.setUniform3f("cSize", csize.get());
		

		fbo.draw(0, 0);

		shader.end();
		fbo.end();
	}

	void bang(int& id) {
		if (bangFlags[id]) {
			float coin = ofRandom(1.);
			if (coin < 0.2) {
				kFactor.to(ofRandom(0.6, 0.95));
			} else if (coin < 0.4) {
				offset.to(ofRandom(0.75, 1.15));
			} else if (coin < 0.6) {
				csize.toX(ofRandom(0.5, 1.));
			} else if (coin < 0.8) {
				csize.toY(ofRandom(0.5, 1.));
			} else if (coin < 1.) {
				csize.toX(ofRandom(0.5, 1.));
			}
		}
	}

private:
	ofShader shader;
	Util::SmoothVal kFactor;
	Util::SmoothVal offset;
	Util::SmoothPoint csize;
};