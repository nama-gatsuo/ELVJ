#pragma once
#include "vector"
#include "BaseLayer.h"
#include "ofTypes.h"
#include "ofGraphics.h"

class Mixer {
public:
	
	Mixer() {}

	void update() {
		for (auto layer : layers) {
			if (layer->isActive()) {
				layer->render();
			}
		}
	}

	void drawLeft() {
		// simple layering
		for (auto layer : layers) {
			if (layer->isActive() && layer->isDrawInLeft()) {
				ofSetColor(255, 255 * layer->getAlpha());
				layer->draw();
			}
		}
	}

	void drawRight() {
		for (auto layer : layers) {
			if (layer->isActive() && layer->isDrawInRight()) {
				ofSetColor(255, 255 * layer->getAlpha());
				layer->draw();
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

private:

	std::vector<ofPtr<BaseLayer>> layers;

};
