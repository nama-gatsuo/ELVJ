#pragma once
#include "ofCamera.h"
#include "Util.h"
#include "Events.h"

using namespace glm;

class StateCam : public ofCamera {
public:
	enum State { STRAIGHT = 0, ARROUND, RAMBLE };
	
	StateCam() : ofCamera(), time(0.), state(STRAIGHT), counter(0) {
		// space size -256 - 256
		setFarClip(512);
		setNearClip(0.1);
		
		ofAddListener(Events::CameraModeChange, this, &StateCam::onCameraModeChange);
	}

	~StateCam() {
		ofRemoveListener(Events::CameraModeChange, this, &StateCam::onCameraModeChange);
	}

	void onCameraModeChange(int& state) {

		this->state = static_cast<State>(state);
		
	}
	
	void update() {
		time += 0.005;
		if (time > TWO_PI) time -= TWO_PI;

		if (state == STRAIGHT) {

			vec3 p = getGlobalPosition();
			float x = sin(time) * 100.;
			float y = (cos(time * 0.03) + 1.4) * 10.;
			float z = -time * 96. + 256.;
			vec3 np(x, y, z);
			vec3 dir = np - p;
			setGlobalPosition(np);
			lookAt(np + dir, vec3(0, 1, 0));

		} else if (state == ARROUND) {

			float radius = 128 + 128 * sin(time * 0.1);
			float x = radius * sin(time);
			float y = 32 * sin(time * 0.5) + 32;
			float z = radius * cos(time);
			setGlobalPosition(vec3(x, y, z));
			lookAt(vec3(0));

		} else if (state == RAMBLE) {
			
			counter += 1;
			if (counter > 240) {
				counter = 0;

				float x = ofRandom(-256, 256);
				float y = ofRandom(0, 64);
				float z = ofRandom(-256, 256);

				sp.to(vec3(x, y, z));
			}
			sp.update();
			
			setGlobalPosition(sp.get());
			lookAt(vec3(0));

		}
	}

	float getLinearScalar() const {
		return 1. / (getFarClip() - getNearClip());
	}

private:
	float time;
	State state;
	int counter;
	Util::SmoothPoint sp;
};
