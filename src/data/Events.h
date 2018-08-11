#pragma once
#include "ofEvents.h"

struct LayerAlpha {
	LayerAlpha(int layer, float alpha) : layer(layer), alpha(alpha) {}
	int layer;
	float alpha;
};

class Events {
public:
	static ofEvent<LayerAlpha> LayerAlphaChange;
	static ofEvent<int> ToggleObject;
};