#pragma once
#include "BaseObject.h"

using namespace glm;

class CityObject : public BaseObject {
public:
	CityObject() : BaseObject() {
		
		shader.load("");

		const int wn = 512;
		const int hn = 512;

		const int initialSize = 64;

		for (int w = 0; w < wn; w += initialSize) {
			for (int h = 0; h < hn; h += initialSize) {
				subdivide(w, h, initialSize, 0);
			}
		}



	}
	
	void update() {
		
	}
	
	void draw(float lds) {
		


	}

	void bang() {
		
	}

private:

	void subdivide(int x, int y, int size, int level) {
		const unsigned maxlevel = 4;

	}
	
	void tower() {
		
	}

}; 