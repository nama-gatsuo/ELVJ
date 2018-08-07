#pragma once
#include "ofShader.h"
#include "ofVboMesh.h"

class BaseObject {
public:
	BaseObject() {}
	virtual void update() = 0;
	virtual void draw(float lds) = 0;

	virtual void bang() = 0;

protected:
	ofVboMesh mesh;
	ofShader shader;
};