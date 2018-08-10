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
		if (gbuffer == nullptr) {
			gbuffer = std::make_shared<ofxDeferred::GBuffer>();
			gbuffer->setup(w, h);
		}
		
		if (cam == nullptr) {
			cam = std::make_shared<ofEasyCam>();
		}

		processor.init(w, h);
		processor.setGBuffer(gbuffer);

		auto s = processor.createPass<SsaoPass>();
		s->setDarkness(1.);
		s->setOcculusionRadius(1.);
		processor.createPass<HdrBloomPass>();
	}
	ofFbo& getFbo() {
		return processor.getFbo();
	}

	void render() {
		gbuffer->begin(*cam);
		for (auto& obj : objects) {
			obj->update();
			obj->draw(1. / (cam->getFarClip() - cam->getNearClip()));
		}
		gbuffer->end();
	}

	template<class T>
	ofPtr<T> addObject() {
		ofPtr<T> obj = std::make_shared<T>();
		objects.push_back(obj);
		return obj;
	}

protected:
	static ofPtr<ofxDeferred::GBuffer> gbuffer; // share in three layer
	static ofPtr<ofEasyCam> cam;
	
	BaseProcessor processor;
	std::vector<ofPtr<BaseObject>> objects;
};