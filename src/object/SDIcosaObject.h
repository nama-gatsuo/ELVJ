#pragma once

#include "ofMain.h"
#include "BaseObject.h"
#include "Util.h"

class SDIcosaObject : public BaseObject {
public:
	SDIcosaObject(int id) : BaseObject(id), isBroken(false) {
		shader.load("shader/scene/broken.vert", "shader/customShader.frag");

		ofMesh base = ofMesh::icosphere(SIZE, 0);
		for (int i = 0; i < 20; i++) {

			ofSeedRandom(0);
			glm::vec3 v[3];
			v[0] = base.getVertex(base.getIndex(i * 3));
			v[1] = base.getVertex(base.getIndex(i * 3 + 1));
			v[2] = base.getVertex(base.getIndex(i * 3 + 2));

			itr(v, 0);

		}

		seed.to(0.);
	}

	void update() {
		seed.update();
	}

	void draw(float lds) {

		shader.begin();
		shader.setUniform1f("lds", lds);
		shader.setUniform1f("seed", seed.get());

		mesh.draw();

		shader.end();

	}

	void bang(int& id) {
		
		if (bangFlags[id]) {
			if (isBroken) {
				seed.to(0.);
				isBroken = false;
			} else {
				seed.to(1.);
				isBroken = true;
			}
		}
		
	}

private:
	void createTri(glm::vec3 * v) {
		mesh.addVertex(v[0]);
		mesh.addVertex(v[1]);
		mesh.addVertex(v[2]);

		ofFloatColor c;
		if (ofRandom(1.) < 0.01) c = ofFloatColor(0.5, 1.3, 2.);
		else c = ofFloatColor(0.1);

		glm::vec3 n = glm::normalize(glm::cross(v[2] - v[0], v[1] - v[0]));

		for (int i = 0; i < 3; i++) {
			mesh.addColor(c);
			mesh.addNormal(n);
		}

	}

	void itr(glm::vec3 * v, int lev) {

		if (lev > MAX_LEV) {
			createTri(v);
			return;
		}

		glm::vec3 n = glm::normalize(glm::cross(v[2] - v[0], v[1] - v[0]));
		glm::vec3 c = (v[0] + v[1] + v[2]) / 3.;
		lev++;

		for (int i = 0; i < 3; i++) {

			glm::vec3 nv[3];

			nv[0] = c + n * SIZE * H_FACTOR * pow(0.53, lev);
			nv[1] = v[i];
			nv[2] = i == 2 ? v[0] : v[i + 1];

			float s = (1. - F_FACTOR) * 0.5;
			glm::vec3 nc = c * F_FACTOR + (nv[1] + nv[2]) * s;

			for (int j = 0; j < 3; j++) {

				glm::vec3 nnv[3];
				nnv[0] = nc;
				nnv[1] = nv[j];
				nnv[2] = j == 2 ? nv[0] : nv[j + 1];

				glm::vec3 n = glm::normalize(glm::cross(nv[2] - nv[0], nv[1] - nv[0]));

				if (j == 1) {
					if (lev == 1) continue;
					createTri(nnv);
				} else {
					itr(nnv, lev);
				}

			}

		}

	}

	const int MAX_LEV = 4;
	const float SIZE = 128;
	const float H_FACTOR = -0.54;
	const float F_FACTOR = 0.33;

	ofVboMesh mesh;
	ofShader shader;

	Util::SmoothVal seed;
	bool isBroken;
};