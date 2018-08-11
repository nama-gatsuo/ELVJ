#pragma once
#include "vector"
#include "BaseLayer.h"
#include "ofTypes.h"
#include "ofGraphics.h"
#include "Events.h"

class Mixer {
public:
	
	Mixer() {
		ofAddListener(Events::LayerAlphaChange, this, &Mixer::onChangeLayerAlpha);
	}

	~Mixer() {
		ofRemoveListener(Events::LayerAlphaChange, this, &Mixer::onChangeLayerAlpha);
	}

	void onChangeLayerAlpha(LayerAlpha& e) {
		if (hasData(e.layer)) layers[e.layer]->setAlpha(e.alpha);
	}


	void update() {
		for (auto layer : layers) {
			if (layer->isActive()) {
				if (layer->isActive()) layer->render();
			}
		}
	}

	void drawLeft() {
		// simple layering
		for (auto layer : layers) {
			if (layer->isActive() && layer->isDrawInLeft()) {
				ofSetColor(255, 255 * layer->getAlpha());
				layer->getFbo().draw(0, 0);
			}
		}
	}

	void drawRight() {
		for (auto layer : layers) {
			if (layer->isActive() && layer->isDrawInRight()) {
				ofSetColor(255, 255 * layer->getAlpha());
				layer->getFbo().draw(0, 0);
			}
		}
	}

	template<class T>
	ofPtr<T> addLayer() {
		ofPtr<T> layer = std::make_shared<T>(ofGetWidth() / 2, ofGetHeight());
		layers.push_back(layer);
		return layer;
	}

	
	const size_t getSize() const {
		return layers.size();
	}

	bool hasData(int id) {
		return id < layers.size() && id >= 0;
	}

private:

	std::vector<ofPtr<BaseLayer>> layers;

};
