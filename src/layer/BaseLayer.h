#pragma once
#include "ofFbo.h"

class BaseLayer {
public:
	enum DrawArea { LEFT = 0, RIGHT = 1, MIX = 2 };

	BaseLayer(int w, int h) {
		activeInBin.assign(7, false);
	}

	virtual void render() = 0;
	virtual const ofFbo& getFbo() const = 0;
	virtual void draw() const = 0;
	
	void setDrawArea(int i, bool flag) { this->activeInBin[i] = flag; }
	bool isActive() { 
		for (auto flag : activeInBin) {
			if (flag) return true;
		}
		return false;
	}

private:
	vector<bool> activeInBin;
};