#pragma once
#include "ofFbo.h"

class BaseLayer {
public:
	enum Mode { LEFT, RIGHT, BOTH };

	BaseLayer(int w, int h) : alpha(0.) {}

	virtual void render() = 0;
	virtual ofFbo& getFbo() = 0;

	void setAlpha(float alpha) { this->alpha = alpha; }
	float getAlpha() { return alpha; }
	
	bool isActive() { return alpha < 0.001; }
	
	void setDrawArea(const Mode& mode) {
		if (mode == LEFT) {
			bDrawInLeft = true;
			bDrawInRight = false;
		} else if (mode == RIGHT) {
			bDrawInLeft = false;
			bDrawInRight = true;
		} else if (mode == BOTH) {
			bDrawInLeft = bDrawInRight = true;
		}
	}

	bool isDrawInLeft() { return bDrawInLeft; }
	bool isDrawInRight() { return bDrawInRight; }

private:
	float alpha;
	bool bDrawInLeft; bool bDrawInRight;
};