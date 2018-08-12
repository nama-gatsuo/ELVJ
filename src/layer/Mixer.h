#pragma once
#include "vector"
#include "BaseLayer.h"
#include "ofTypes.h"
#include "ofGraphics.h"
#include "Events.h"
#include "Constants.h"

class Mixer {
public:
	enum Mode { ALPHA_BLEND, TWO_CHAN_MIX };
	struct State {
		State() : mode(ALPHA_BLEND), mixLayer(0), mix{ 0,0 } {}
		State(const State& copy) : mode(copy.mode), mixLayer(copy.mixLayer), mix{ copy.mix[0], copy.mix[1] } {}

		Mode mode;
		int mixLayer;
		int mix[2];
	};

	Mixer() {

		mixShader.load("shader/vfx/passThru.vert", "shader/pfx/TwoChanMix.frag");

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

	void drawIn(int i) {
		// simple layering

		switch (state[i].mode) {
			case ALPHA_BLEND: {
				for (auto layer : layers) {
					if (layer->isActive() && layer->isDrawIn(i)) {
						ofSetColor(255, 255 * layer->getAlpha());
						layer->getFbo().draw(0, 0, Constants::screenSize.x, Constants::screenSize.y);
					}
				}
				
			} break;
			case TWO_CHAN_MIX: {
				
				mixShader.begin();
				mixShader.setUniformTexture("tex1", layers[state[i].mix[0]]->getFbo().getTexture(0), 1);
				mixShader.setUniformTexture("tex2", layers[state[i].mix[1]]->getFbo().getTexture(0), 2);

				layers[state[i].mixLayer]->getFbo().draw(0, 0, Constants::screenSize.x, Constants::screenSize.y);
				mixShader.end();

			} break;
			default: break;
		}
		
		
	}

	template<class T>
	ofPtr<T> addLayer() {
		ofPtr<T> layer = std::make_shared<T>(Constants::renderSize.x, Constants::renderSize.y);
		layers.push_back(layer);
		return layer;
	}


	const size_t getSize() const {
		return layers.size();
	}

	bool hasData(int id) {
		return id < layers.size() && id >= 0;
	}

	bool setMixerState(int i, const State& state) {
		if (hasData(state.mixLayer) && hasData(state.mix[0]) && hasData(state.mix[1])) {
			this->state[i] = state;
		} else {
			ofLogWarning() << "specified layer is out of range";
		}
	}

private:
	std::vector<ofPtr<BaseLayer>> layers;
	State state[2];
	ofShader mixShader;

};
