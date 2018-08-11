#pragma once
#include "BaseObject.h"

using namespace glm;

class CityObject : public BaseObject {
public:
	CityObject() : BaseObject() {
		
		shader.load("shader/scene/broken");

		const int wn = 512;
		const int hn = 512;

		const int initialSize = 128;

		for (int w = - wn / 2; w < wn / 2; w += initialSize) {
			for (int h = - hn; h < hn / 2; h += initialSize) {
				subdivide(w, h, initialSize, 0);
			}
		}
		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	}
	
	void update() {
		
	}
	
	void draw(float lds) const {
		shader.begin();
		shader.setUniform1f("lds", lds);

		mesh.draw();

		shader.end();
	}

	void bang() {
		
	}

private:

	void subdivide(int x, int y, int size, int level) {
		const int maxlevel = 2;

		mat4 m = translate(vec3(x, 0, y)) * scale(vec3(size * 0.9));

		if (level >= maxlevel) { 
			tower(m);
			return;
		}

		float coin = ofRandom(1.);
		if (coin < 0.5) {
			int ns = size / 2;
			int nl = level + 1;

			subdivide(x, y, ns, nl);
			subdivide(x + ns, y, ns, nl);
			subdivide(x, y + ns, ns, nl);
			subdivide(x + ns, y + ns, ns, nl);
		} else {
			tower(m);
		}

	}
	
	void tower(const mat4& m) {
		mat4 tm(m);

		for (int i = 0; i < 8; i++) {
			
			if (ofRandom(1.) < 0.4) tm = tm * scale(vec3(1.2));
			else tm = tm * scale(vec3(0.8));

			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					
					mat4 ttm = tm * translate(vec3(0.25 + 0.5 * j, 0., 0.25 + 0.5 * k));

					if (ofRandom(1.) < 0.4) {
						
						ttm = ttm * scale(vec3(0.5));
						beam(ttm);

					} else {
						
						if (ofRandom(1.) < 0.4) ttm = ttm * scale(vec3(0.3, 0.2, 0.3));
						else ttm = ttm * scale(vec3(0.4, 0.35, 0.4));
						
						room(ttm);
					}
				}
			}
			
			if (ofRandom(1.) < 0.4) tm = tm * translate(vec3(0., .4, 0.));
			else tm = tm * translate(vec3(0., .1, 0.));

		}
	}

	void beam(const mat4& m) {

		ofFloatColor c(0.2);
		mat4 tm(m);

		if (ofRandom(1.) < 0.5) {
			tm = tm * rotate((float)HALF_PI, vec3(0, 1, 0));
		}

		// vertical
		mat4 ttm = tm * translate(vec3(0, 0, -0.05));
		ttm = ttm * scale(vec3(0.06, 1, 0.02));
		addBox(ttm, c);

		ttm = tm * translate(vec3(0, 0, 0.05));
		ttm = ttm * scale(vec3(0.06, 1, 0.02));
		addBox(ttm, c);

		ttm = tm * translate(vec3(0, 0.5, 0));
		ttm = ttm * scale(vec3(0.06, 0.01, 0.1));
		addBox(ttm, c);

		ttm = tm * translate(vec3(-0.05, 0, 0));
		ttm = ttm * scale(vec3(0.02, 0.4, 0.1));
		addBox(ttm, c);

		ttm = tm * translate(vec3(0.05, 0, 0));
		ttm = ttm * scale(vec3(0.02, 0.4, 0.1));
		addBox(ttm, c);

	}

	void room(const mat4& m) {
		
		ofFloatColor c(0.1);
		ofFloatColor lc(1.1);

		float coin = ofRandom(1.);

		if (coin < 0.4) {

			addBox(m * scale(vec3(0.9, 1., 0.9)), c);
			addBox(m * scale(vec3(1., 0.9, 1.)), c);

		} else if (coin < 0.7) {
			
			mat4 tm = m * translate(vec3(0, 0.5, 0));
			tm = tm * scale(vec3(1., 0.1, 1.));
			addBox(tm, c);

			tm = m * translate(vec3(0, 0.3, 0));
			tm = tm * scale(vec3(1., 0.1, 1.));
			addBox(tm, c);

			tm = m * translate(vec3(0, 0.1, 0));
			tm = tm * scale(vec3(1., 0.1, 1.));
			addBox(tm, c);

			tm = m * translate(vec3(0, -0.3, 0));
			tm = tm * scale(vec3(1., 0.4, 1.));
			addBox(tm, c);
			
			tm = m * scale(vec3(0.8));
			addBox(tm, lc);

		} else {

			float h = ofRandom(1.);
			float w = ofRandom(0.45);

			for (int j = 0; j < 2; j++) {
				for (int k = 0; k < 2; k++) {
					mat4 tm = m * translate(vec3(0.25 + 0.5 * j, 0., 0.25 + 0.5 * k));
					tm = tm * scale(vec3(ofRandom(0.45), h, ofRandom(0.45)));
					addBox(tm, c);
				}
			}
		}

	}

	void addBox(const mat4& _m, const ofFloatColor& _c) {

		ofMesh box = ofMesh::box(1., 1., 1., 1, 1, 1);

		for (int i = 0; i < box.getNumVertices(); i++) {
			vec4 v = _m * vec4(box.getVertex(i), 1.f);
			//vec4 n = inverse(transpose(_m)) * vec4(box.getNormal(i), 0.f);

			box.setVertex(i, v);
			//box.setNormal(i, n);
			box.addColor(_c);
		}

		mesh.append(box);

	}

}; 