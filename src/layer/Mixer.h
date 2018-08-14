#pragma once
#include "vector"
#include "BaseLayer.h"
#include "MixLayer.h"
#include "ofTypes.h"
#include "ofGraphics.h"
#include "Events.h"
#include "Constants.h"

class Mixer {
public:

	Mixer() {
		layersInBin[0].assign(2, ofPtr<BaseLayer>());
		layersInBin[1].assign(2, ofPtr<BaseLayer>());
		alphas.assign(5, 0.);

		ofAddListener(Events::LayerAlphaChange, this, &Mixer::onChangeLayerAlpha);
		ofAddListener(Events::DrawAreaStateChange, this, &Mixer::onStateChange);
		
		auto l0 = addLayer<ConstantsLayer>();
		
		setLayerInBin(0, 0, 0);
		setLayerInBin(1, 0, 0);
		setLayerInBin(0, 1, 0);
		setLayerInBin(1, 1, 0);

		mixLayer = std::make_shared<MixLayer>(Constants::renderSize, -1);
		mixLayer->setLayer(0, l0);
		mixLayer->setLayer(1, l0);
		mixLayer->setMixLayer(l0);
	}

	~Mixer() {
		ofRemoveListener(Events::LayerAlphaChange, this, &Mixer::onChangeLayerAlpha);
		ofRemoveListener(Events::DrawAreaStateChange, this, &Mixer::onStateChange);
	}

	void onChangeLayerAlpha(LayerAlpha& e) {
		alphas[e.layer] = e.alpha;
		ofLogNotice() << "change alpha: " << e.alpha;
	}

	void onStateChange(DrawAreaState& state) {
		ofLogNotice() << "bin: " << state.binId << " layer: " << state.layerId;

		if (state.binId == 0) {
			mixLayer->setMixLayer(layers[state.layerId]);
		} else if (state.binId <= 2) {
			mixLayer->setLayer(state.binId - 1, layers[state.layerId]);
		} else if (state.binId <= 4) {
			layersInBin[0][state.binId - 3]->setDrawArea(state.binId, false);
			layersInBin[0][state.binId - 3] = layers[state.layerId];
			layersInBin[0][state.binId - 3]->setDrawArea(state.binId, true);
		} else if (state.binId <= 6) {
			layersInBin[1][state.binId - 5]->setDrawArea(state.binId, false);
			layersInBin[1][state.binId - 5] = layers[state.layerId];
			layersInBin[1][state.binId - 5]->setDrawArea(state.binId, true);
		}
	}

	void update() {
		if (alphas[0] > 0.001) {
			mixLayer->render();
		}

		for (auto layer : layers) {
			if (layer != nullptr && layer->isActive()) layer->render();
		}
	}

	void drawIn(int i) {

		for (int j = 0; j < 2; j++) {
			if (layersInBin[i][j] != nullptr && alphas[1 + i * 2 + j] > 0.001) {
				ofSetColor(255, 255 * alphas[1 + i * 2 + j]);
				layersInBin[i][j]->draw();
			}
		}

		if (i == 0 && alphas[0] > 0.001) {
			ofSetColor(255, 255 * alphas[0]);
			mixLayer->draw();
		}

	}

	template<class T>
	ofPtr<T> addLayer() {
		ofPtr<T> layer = std::make_shared<T>(Constants::renderSize, layers.size());
		layers.push_back(layer);
		return layer;
	}

	const size_t getSize() const {
		return layers.size();
	}

	bool hasData(int id) {
		return id < layers.size() && id >= 0;
	}

	void setLayerInBin(int leftOrRight, int zeroOrOne, int layerId) {
		int id = 3 + leftOrRight * 2 + zeroOrOne;
		if (layersInBin[leftOrRight][zeroOrOne] != nullptr) {
			layersInBin[leftOrRight][zeroOrOne]->setDrawArea(id, false);
		}
		layersInBin[leftOrRight][zeroOrOne] = layers[layerId];
		layersInBin[leftOrRight][zeroOrOne]->setDrawArea(id, true);
	}

private:
 
	std::vector<ofPtr<BaseLayer>> layersInBin[2];
	std::vector<float> alphas;

	// layers
	// Constants, World_PtotoReal, World_Edge, Tex_Fourier, Tex_Noise
	std::vector<ofPtr<BaseLayer>> layers;

	ofPtr<MixLayer> mixLayer;

};
