#pragma once
#include "BaseObject.h"
#include "Util.h"
#include "glm/glm.hpp"

class OctaWarm {
public:
	OctaWarm(const ofVboMesh& _mesh) {
		mesh = _mesh;

		params1 = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)) * 6;
		params2 = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1)) * 20;

	}

	glm::vec3 getCurvePoint(const glm::vec3& params1, const glm::vec3& params2, float t, float phase) {
		glm::vec3 v(
			sin(params1.x * t + (1 + sin(params2.x * t + phase) * 0.5)),
			sin(params1.y * t + (1 + sin(params2.y * t + phase) * 0.5)),
			sin(params1.z * t + (1 + sin(params2.z * t + phase) * 0.5))
		);
		return v;
	}

	void update() {

		t0 += 0.003;
		if (t0 > 1.) isDead = true;
		phase += 0.00279;

		progress = sin(t0 * PI);

	}

	void draw() {

		glm::vec3 Pp = getCurvePoint(params1, params2, t0 - deltaTheta, phase);
		glm::vec3 P1 = getCurvePoint(params1, params2, t0, phase);
		glm::vec3 T1 = P1 - Pp;
		float t = t0 - deltaTheta;

		for (int i = 0; i < 40; i++) {

			glm::vec3 P = getCurvePoint(params1, params2, t, phase);
			glm::vec3 T = P - P1;
			glm::vec3 N = T - T1;
			glm::vec3 B = glm::normalize(glm::cross(T, N));

			glm::vec3 xAxis = B;
			glm::vec3 zAxis = glm::normalize(T);
			glm::vec3 yAxis = glm::normalize(glm::cross(xAxis, zAxis));

			glm::mat4 mat = glm::mat4(
				xAxis.x, xAxis.y, xAxis.z, 0.0,
				yAxis.x, yAxis.y, yAxis.z, 0.0,
				zAxis.x, zAxis.y, zAxis.z, 0.0,
				P.x, P.y, P.z, 1.0
			);

			ofPushMatrix();
			ofScale(256, 256, 256);
			ofMultMatrix(mat);
			ofScale(progress, progress, progress);

			mesh.draw();

			ofPopMatrix();

			P1 = P;
			T1 = T;
			t += deltaTheta;

		}

	}

	bool isDead = false;
	
private:

	float t0 = 0.;
	float progress = 0.;
	float phase = 20.;
	float deltaTheta = 0.005;

	glm::vec3 params1, params2;

	ofVboMesh mesh;
};

class WarmObject : public BaseObject {
public:
	WarmObject(int id) : BaseObject(id) {

		shader.load("shader/scene/wireframe.vert", "shader/scene/wireframe.frag", "shader/scene/wireframe.geom");
		
		glm::vec3 ov[6] = {
			glm::vec3(1,0,0), glm::vec3(-1,0,0), glm::vec3(0,1,0),
			glm::vec3(0,-1,0), glm::vec3(0,0,1), glm::vec3(0,0,-1)
		};

		unsigned oi[24] = {
			0, 2, 4, 0, 4, 3, 0, 3, 5, 0, 5, 2,
			1, 2, 5, 1, 5, 3, 1, 3, 4, 1, 4, 2
		};

		for (int i = 0; i < 24; i += 3) {
			glm::vec3 v1 = ov[oi[i]] * 0.1;
			glm::vec3 v2 = ov[oi[i + 1]] * 0.1;
			glm::vec3 v3 = ov[oi[i + 2]] * 0.1;

			mesh.addVertex(v1);
			mesh.addVertex(v2);
			mesh.addVertex(v3);

		}

		mesh.setMode(OF_PRIMITIVE_TRIANGLES);
	}

	void update() {
	
		vector<OctaWarm>::iterator it;
		for (it = ows.begin(); it < ows.end();) {
			it->update();

			if (it->isDead) it = ows.erase(it);
			else it++;
		}
		
	}

	void draw(float lds) {
		vector<OctaWarm>::iterator it;

		shader.begin();
		shader.setUniform1f("lds", lds);
		shader.setUniform1f("wireWidth", 0.1);
		shader.setUniform1i("isDrawFace", 0);

		for (auto& it : ows) {
			it.draw();
		}

		shader.end();
	}

	void bang(int& i) {

		if (bangFlags[i]) {
			if (ows.size() > MAX_COUNT) return;
			ows.push_back(OctaWarm(mesh));
		}
	}

private:
	vector<OctaWarm> ows;
	ofShader shader;
	int MAX_COUNT = 20;
	ofVboMesh mesh;

};