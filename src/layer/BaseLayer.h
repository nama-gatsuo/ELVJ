#pragma once
#include "ofFbo.h"
#include "ofEventUtils.h"
#include "Events.h"

class BaseLayer {
public:
	enum DrawArea { LEFT = 0, RIGHT = 1, MIX = 2 };

	BaseLayer(int w, int h) {
		activeInBin.assign(7, false);
		bangFlags.assign(4, false);
		ofAddListener(Events::Bang, this, &BaseLayer::bang);
	}
	
	~BaseLayer() {
		ofRemoveListener(Events::Bang, this, &BaseLayer::bang);
	}

	virtual void render() = 0;
	virtual const ofFbo& getFbo() const = 0;
	virtual void draw() const = 0;
	virtual void bang(int& id) = 0;

	void setDrawArea(int i, bool flag) { this->activeInBin[i] = flag; }
	bool isActive() { 
		for (auto flag : activeInBin) {
			if (flag) return true;
		}
		return false;
	}

	void toggleReactBang(int id) {
		bangFlags[id] = !bangFlags[id];
	}

private:
	vector<bool> activeInBin;
	std::vector<bool> bangFlags;
};