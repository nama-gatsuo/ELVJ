#pragma once
#include "ofTypes.h"
#include "GBuffer.hpp"
#include "BaseObject.h"

class BaseWorld {
public:
	BaseWorld(int w, int h) {
		gbuffer = make_shared<ofxDeferred::GBuffer>();
		gbuffer->setup(w, h);
	}

	void update() {
		
		gbuffer->begin(cam, true);
		for (auto& obj : objects) {
			if (obj->isVisible()) {
				obj->update();
				obj->draw(1. / (cam.getFarClip() - cam.getNearClip()));
			}
		}
		gbuffer->end();

	}

	ofPtr<ofxDeferred::GBuffer> getGBufferPointer() {
		return gbuffer;
	}

	const ofCamera& getCam() const {
		return cam;
	}

	template<class T>
	ofPtr<T> addObject() {
		ofPtr<T> obj = std::make_shared<T>();
		objects.push_back(obj);
		return obj;
	}

private:
	ofEasyCam cam;
	ofPtr<ofxDeferred::GBuffer> gbuffer;
	std::vector<ofPtr<BaseObject>> objects;

};
