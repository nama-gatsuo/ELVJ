#pragma once
#include "ofFbo.h"

class BaseLayer {
public:
	enum DrawArea { LEFT = 0, RIGHT = 1 };

	BaseLayer(int w, int h) : alpha(0.), bDraw{ false, false } {
	}

	virtual void render() = 0;
	virtual const ofFbo& getFbo() const = 0;
	virtual void draw() const = 0;

	void setAlpha(float alpha) { this->alpha = alpha; }
	float getAlpha() { return alpha; }
	
	bool isActive() { return alpha > 0.001 && (bDraw[0] || bDraw[1]); }
	
	bool isDrawIn(int i) { return bDraw[i]; }
	void toggleDrawIn(int i) { bDraw[i] = !bDraw[i]; }

private:
	float alpha;
	bool bDraw[2];
};