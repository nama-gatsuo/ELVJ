#pragma once
#include "TwoLayer.h"
#include "ofGraphics.h"
#include "ofShader.h"
#include "ofUtils.h"
#include "ofMath.h"

class RayMarchLayer : public TwoLayer {
public:
	RayMarchLayer(const glm::ivec2& size, int id) : TwoLayer(size, id) {
		shader.load("shader/vfx/passThru.vert", "shader/scene/raymarch/Tgrad.frag");
	}

	void render() {
		fbo.begin();
		ofClear(0.);

		shader.begin();
		shader.setUniform2f("res", Constants::renderSize.x, Constants::renderSize.y);

		shader.setUniform3f("cp", glm::vec3(sin(ofGetElapsedTimef()) * 0.1, 1., cos(ofGetElapsedTimef() * 0.1)));
		shader.setUniform4f("color", ofFloatColor(.1));

		shader.setUniform1f("minr", ofClamp(sin(ofGetElapsedTimef()), 0.2, 0.5));
		shader.setUniform1f("maxr", ofClamp(cos(ofGetElapsedTimef()) + 1., 0.75, 1.25));
		shader.setUniform1f("minc", ofClamp(-sin(ofGetElapsedTimef() * 0.1) * 0.2 - 9., -1.0, -0.8));
		shader.setUniform1f("maxc", ofClamp(-cos(ofGetElapsedTimef() * 0.3) + 0.9, 0.8, 1.));
		shader.setUniform1f("scale", ofClamp(sin(ofGetElapsedTimef() * 0.2) + 0.3 - 3.1, -3.2, -3.));
		shader.setUniform3f("offset", glm::vec3(1.2, 49.0, 1.4));
		shader.setUniform3f("p0", glm::vec3(0.0, 1.59, -1.0));
		
		shader.setUniform1f("equiFactor", ofClamp( (sin(ofGetElapsedTimef())) * 4., 0., 1.));

		fbo.draw(0, 0);

		shader.end();
		fbo.end();
	}

private:
	ofShader shader;
};