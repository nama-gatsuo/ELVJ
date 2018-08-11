#pragma once
#include "ofCamera.h"

using namespace glm;

class StateCam : public ofCamera {
public:
	enum State { STRAIGHT, ARROUND, RAMBLE };
	
	StateCam() : ofCamera(), time(0.), state(STRAIGHT), fovy(60) {
		// space size -256 - 256
		setFarClip(512);
		setNearClip(0.1);
		setFov(fovy);
		
		ofAddListener(ofEvents().keyPressed, this, &StateCam::onKeyPressed);
	}

	~StateCam() {
		ofRemoveListener(ofEvents().keyPressed, this, &StateCam::onKeyPressed);
	}

	void onKeyPressed(ofKeyEventArgs& key) {

		if (key.key == 'a') changeState(STRAIGHT);
		else if (key.key == 's') changeState(ARROUND);
		else if (key.key == 'd') changeState(RAMBLE);
		
	}

	void changeState(State s) {
		state = s;
	}

	void update() {
		time += 0.005;
		if (time > TWO_PI) time -= TWO_PI;

		if (state == STRAIGHT) {
			float z = -time * 96. + 256.;

			setGlobalPosition(vec3(0, 0, z));

		} else if (state == ARROUND) {
			
		} else if (state == RAMBLE) {
			
		}
	}

	float getLinearScalar() const {
		return 1. / (getFarClip() - getNearClip());
	}

private:
	float time;
	State state;
	float fovy;

};
