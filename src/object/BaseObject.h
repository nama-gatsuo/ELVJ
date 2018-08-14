#pragma once
#include "ofShader.h"
#include "ofVboMesh.h"
#include "ofEventUtils.h"
#include "Events.h"

class BaseObject {
public:
	BaseObject(int id) : visible(false), id(id) {
		bangFlags.assign(4, false);
		ofAddListener(Events::Bang, this, &BaseObject::bang);
		ofAddListener(Events::ToggleBangStateObj, this, &BaseObject::toggleBangState);
	}

	~BaseObject() {
		ofRemoveListener(Events::Bang, this, &BaseObject::bang);
		ofRemoveListener(Events::ToggleBangStateObj, this, &BaseObject::toggleBangState);
	}

	virtual void update() = 0;
	virtual void draw(float lds) const = 0;

	virtual void bang(int& id) = 0;

	bool isVisible() { return visible; }
	void toggleVisible() { visible = !visible; }

	void toggleBangState(BangStateObj& state) {
		if (state.id == id) {
			bangFlags[state.chan] = !bangFlags[state.chan];
			ofLogNotice() << "clicked " << state.id;
		}
	}

protected:
	const int id;
	ofVboMesh mesh;
	ofShader shader;

	bool visible;
	std::vector<bool> bangFlags;

};