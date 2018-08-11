#pragma once
#include "BaseLayer.h"
#include "ofxDeferredShading.h"
#include "BaseProcessor.h"
#include "BaseWorld.h"

using namespace ofxDeferred;

class ThreeLayer : public BaseLayer {
public:
	ThreeLayer(int w, int h) : BaseLayer(w, h) {
		processor.init(w, h);
	}

	const ofFbo& getFbo() const { return processor.getFbo(); }

	virtual void render() {
		processor.update(world->getCam());
		processor.render();
	}

	void setWorld(ofPtr<BaseWorld> world) {
		this->world = world;
		processor.setGBuffer(world->getGBufferPointer());
	}

protected:
	BaseProcessor processor;
	ofPtr<BaseWorld> world; // 3d objects to share in ThreeLayer
};

// edge detection 3D layer
class EdgeThreeLayer : public ThreeLayer {
public:
	EdgeThreeLayer(int w, int h) : ThreeLayer(w, h) {
		auto e = processor.createPass<EdgePass>();
		e->setEdgeColor(ofFloatColor(1.));
		e->setBackground(ofFloatColor(0.));
		e->setUseReadColor(false);
	}
};

// photo realistc 3D layer
class PRThreeLayer : public ThreeLayer {
public:
	PRThreeLayer(int w, int h) : ThreeLayer(w, h) {
		auto s = processor.createPass<SsaoPass>();
		s->setDarkness(1.);
		s->setOcculusionRadius(3.);
		processor.createPass<HdrBloomPass>();
	}
};
