#pragma once
#include "ofFbo.h"
#include "ofEventUtils.h"
#include "Events.h"

class BaseLayer {
public:
	enum DrawArea { LEFT = 0, RIGHT = 1, MIX = 2 };

	BaseLayer(const glm::ivec2& size, int id) : id(id) {
		activeInBin.assign(7, false);
		bangFlags.assign(4, false);
		bangFlags[3] = true;

		ofAddListener(Events::Bang, this, &BaseLayer::bang);
		ofAddListener(Events::ToggleBangStateLayer, this, &BaseLayer::toggleBangState);
	}
	
	virtual ~BaseLayer() {
		ofRemoveListener(Events::Bang, this, &BaseLayer::bang);
		ofRemoveListener(Events::ToggleBangStateLayer, this, &BaseLayer::toggleBangState);
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

	void toggleBangState(BangStateLayer& state) {
		if (state.id == id) {
			bangFlags[state.chan] = !bangFlags[state.chan];
		}
	}
protected:
	std::vector<bool> bangFlags;
private:
	const int id;
	std::vector<bool> activeInBin;
};