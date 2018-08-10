#pragma once
#include "BaseLayer.h"
#include "GBuffer.hpp"
#include "BaseObject.h"
#include "ofxDeferredShading.h"
#include "BaseProcessor.h"

using namespace ofxDeferred;

class ThreeLayer : public BaseLayer {
public:
	ThreeLayer(int w, int h);

	ofFbo& getFbo() { return processor.getFbo(); }
	void render();

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