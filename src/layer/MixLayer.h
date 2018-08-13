#pragma once
#include "BaseLayer.h"
#include "ofShader.h"
#include "ofTypes.h"
#include "ofGraphics.h"
#include "Events.h"
#include "TwoLayer.h"

class MixLayer : public BaseLayer {
public:

	MixLayer(int w, int h) : BaseLayer(w, h), threshold(0.5) {
		fbo.allocate(w, h, GL_RGBA);
		shader.load("shader/vfx/passThru.vert", "shader/pfx/TwoChanMix.frag");
		
		layers[0] = layers[1] = nullptr;
		
		ofAddListener(Events::MixThresChange, this, &MixLayer::onThresChange);
	}
	
	~MixLayer() {
		ofRemoveListener(Events::MixThresChange, this, &MixLayer::onThresChange);
	}

	void onThresChange(float& thres) {
		threshold = thres;
	}

	void render () {
		fbo.begin();
		ofClear(0);

		shader.begin();
		shader.setUniformTexture("tex1", layers[0]->getFbo().getTexture(0), 1);
		shader.setUniformTexture("tex2", layers[1]->getFbo().getTexture(0), 2);
		shader.setUniform1f("thres", threshold);

		mixLayer->getFbo().draw(0, 0);
		shader.end();

		fbo.end();
	}

	const ofFbo& getFbo() const {
		return fbo;
	}

	void draw() const { fbo.draw(0, 0); }

	void setLayer(int i, ofPtr<BaseLayer> layer) {
		if (layers[i] != nullptr) layers[i]->setDrawArea(i + 1, false);
		layers[i] = layer;
		layers[i]->setDrawArea(i + 1, true);
	}

	void setMixLayer(ofPtr<BaseLayer> mixLayer) {
		if (this->mixLayer != nullptr) this->mixLayer->setDrawArea(0, false);
		this->mixLayer = mixLayer;
		this->mixLayer->setDrawArea(0, true);
	}

private:
	ofFbo fbo;
	ofShader shader;
	ofPtr<BaseLayer> layers[2];
	ofPtr<BaseLayer> mixLayer;

	float threshold;

};