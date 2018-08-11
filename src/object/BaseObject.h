#pragma once
#include "ofShader.h"
#include "ofVboMesh.h"

class BaseObject {
public:
	BaseObject() : visible(true) {}
	virtual void update() = 0;
	virtual void draw(float lds) const = 0;

	virtual void bang() = 0;

	bool isVisible() { return visible; }
	void toggleVisible() { visible = !visible; }

protected:
	ofVboMesh mesh;
	ofShader shader;

	bool visible;
};