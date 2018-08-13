#pragma once
#include "ofEvents.h"

struct LayerAlpha {
	LayerAlpha(int layer, float alpha) : layer(layer), alpha(alpha) {}
	int layer; // 0: F0(mix layer), 1: F1, 2: F2, 3, R0, 4 R1 
	float alpha;
};

struct DrawAreaState {
	int binId; // 0: mix, 1: mix1, 2: mix2, 3:... 
	int layerId;
};

class Events {
public:
	static ofEvent<LayerAlpha> LayerAlphaChange;
	static ofEvent<int> ToggleObject;
	static ofEvent<DrawAreaState> DrawAreaStateChange;
	static ofEvent<float> MixThresChange;
};