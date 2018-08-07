#pragma once
#include "BaseLayer.h"
#include "GBuffer.hpp"
#include "BaseObject.h"

class ThreeLayer : public BaseLayer {
public:
	ThreeLayer(int w, int h) : BaseLayer(w, h) {
		if (!gbuffer.isAllcated()) gbuffer.setup(w, h);
	}

	void render() {
		
		
	}

	ofFbo& getFbo() {
		
	}

protected:

	static ofxDeferred::GBuffer gbuffer;
	static ofEasyCam cam;
};