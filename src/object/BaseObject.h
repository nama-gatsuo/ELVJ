#pragma once
#include "ofShader.h"
#include "ofVboMesh.h"
#include "ofEventUtils.h"
#include "Events.h"

class BaseObject {
public:
	BaseObject() : visible(false) {
		bangFlags.assign(4, false);
		ofAddListener(Events::Bang, this, &BaseObject::bang);
	}

	~BaseObject() {
		ofRemoveListener(Events::Bang, this, &BaseObject::bang);
	}

	virtual void update() = 0;
	virtual void draw(float lds) const = 0;

	virtual void bang(int& id) = 0;

	bool isVisible() { return visible; }
	void toggleVisible() { visible = !visible; }

	void toggleReactBang(int id) {
		bangFlags[id] = !bangFlags[id];
	}

protected:
	ofVboMesh mesh;
	ofShader shader;

	bool visible;
	std::vector<bool> bangFlags;

};