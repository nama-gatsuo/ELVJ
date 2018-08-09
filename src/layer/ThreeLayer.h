#pragma once
#include "BaseLayer.h"
#include "GBuffer.hpp"
#include "BaseObject.h"
#include "ofxDeferredShading.h"
#include "BaseProcessor.h"

using namespace ofxDeferred;

class ThreeLayer : public BaseLayer {
public:
	ThreeLayer(int w, int h) : BaseLayer(w, h) {
		if (!gbuffer.isAllcated()) gbuffer.setup(w, h);
		processor.setGBuffer(ofPtr<GBuffer>(&gbuffer));

		auto s = processor.createPass<SsaoPass>();
		s->setDarkness(1.);
		s->setOcculusionRadius(1.);
		processor.createPass<HdrBloomPass>();
	}
	ofFbo& getFbo() {
		return processor.getFbo();
	}

	void render() {
		gbuffer.begin(cam);
		for (auto& obj : objects) {
			obj->update();
			obj->draw(1. / (cam.getFarClip() - cam.getNearClip()));
		}
		gbuffer.end();
	}

	template<class T>
	ofPtr<T> addObject() {
		ofPtr<T> obj = std::make_shared<T>();
		objects.push_back(obj);
		return obj;
	}

protected:
	static ofxDeferred::GBuffer gbuffer; // share in three layer
	static ofEasyCam cam;
	
	BaseProcessor processor;
	std::vector<ofPtr<BaseObject>> objects;
};