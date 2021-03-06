#pragma once
#include "glm/glm.hpp"
#include "ofMain.h"

using namespace glm;

namespace Util {
	class SmoothPoint {
	public:
		SmoothPoint() : ratio(0.03) {}
		SmoothPoint(const vec3& p) : ratio(0.03), target(p), current(p) {}

		void update() {
			current += (target - current) * ratio;
		}

		void set(const vec3& p) { current = p; }
		void setRatio(float r) { ratio = r; }
		void to(const vec3& p) { target = p; }
		
		void toX(float x) { target.x = x; }
		void toY(float y) { target.y = y; }
		void toZ(float z) { target.z = z; }

		const vec3& get() const { return current; }

	private:
		vec3 target; vec3 current; float ratio;
	};

	class SmoothVal {
	public:
		SmoothVal() : ratio(0.03), target(0), current(0) {}
		SmoothVal(float p) : ratio(0.03), target(p), current(p) {}

		void update() {
			current += (target - current) * ratio;
		}

		void set(float p) {
			current = p;
			target = p;
		}
		void setRatio(float r) { ratio = r; }
		void to(float p) { target = p; }

		float get() const { return current; }

	private:
		float target; float current; float ratio;
	};

	class PhysicVal {
	public:
		PhysicVal() : p(0), v(0), g(-0.01), min(0.), max(1.) {}

		void update() {
			v += g;
			v = clamp(v, -0.4f, 0.4f);
			
			p += v;
			if (p < 0.) v = 0;
			p = clamp(p, min, max);
			
		}
		
		void addForce() {
			v += 0.3f;
		}

		float get() { return p; }

	private:
		float p; float v; float g;
		float min; float max;
	};

};
