#pragma once
#include "ofTypes.h"
#include "GBuffer.hpp"
#include "BaseObject.h"
#include "StateCam.h"

class BaseWorld {
public:
	BaseWorld(int w, int h) {
		gbuffer = make_shared<ofxDeferred::GBuffer>();
		gbuffer->setup(w, h);
		
		ofAddListener(Events::ToggleObject, this, &BaseWorld::toggleObject);
	}

	~BaseWorld() {
		ofRemoveListener(Events::ToggleObject, this, &BaseWorld::toggleObject);
	}

	void update() {
		
		cam.update();

		gbuffer->begin(cam, true);
		for (auto& obj : objects) {
			if (obj->isVisible()) {
				obj->update();
				obj->draw(cam.getLinearScalar());
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

	void toggleObject(int& id) {
		if (hasData(id)) {
			objects[id]->toggleVisible();
		}
	}

	bool hasData(int id) {
		return id < objects.size() && id >= 0;;
	}

private:
	ofPtr<ofxDeferred::GBuffer> gbuffer;
	std::vector<ofPtr<BaseObject>> objects;
	StateCam cam;
};
