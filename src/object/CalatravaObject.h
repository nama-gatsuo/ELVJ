#pragma once
#include "BaseObject.h"
#include "Util.h"

class CalatravaObject : public BaseObject {
public:
	CalatravaObject(int id) : BaseObject(id) {
		shader.load("shader/scene/CalatravaStruct.vert", "shader/customShader.frag");

		shader.begin();
		shader.setUniform1i("total", num);
		shader.end();

		mesh = ofMesh::box(1., 1., 1., 1, 1, 1);

		ofFloatColor col;
		col.set(1.0);

		for (int i = 0; i < mesh.getNumIndices(); i++) {
			mesh.addColor(col);
		}

		fromTrans.setRatio(0.005);
		fromRotate.setRatio(0.005);
		fromScale.setRatio(0.005);
		toTrans.setRatio(0.005);
		toRotate.setRatio(0.005);
		toScale.setRatio(0.005);

		int i = 2;
		bang(i);
	}
	

	void update() {
		fromTrans.update();
		fromRotate.update();
		fromScale.update();
		toTrans.update();
		toRotate.update();
		toScale.update();
	}
	void draw(float lds) {
		shader.begin();
		shader.setUniform1f("lds", lds);
		
		shader.setUniform3f("fromTrans", fromTrans.get());
		shader.setUniform3f("fromRotate", fromRotate.get());
		shader.setUniform3f("fromScale", fromScale.get());
		shader.setUniform3f("toTrans", toTrans.get());
		shader.setUniform3f("toRotate", toRotate.get());
		shader.setUniform3f("toScale", toScale.get());

		mesh.drawInstanced(OF_MESH_FILL, num);

		shader.end();
	}
	
	void bang(int& id) {
		if (bangFlags[id]) {
			fromTrans.to(ofPoint(ofRandom(128), ofRandom(128), ofRandom(128)));
			fromRotate.to(ofPoint(ofRandom(TWO_PI*2.), ofRandom(TWO_PI*2.), ofRandom(TWO_PI*2.)));
			fromScale.to(ofPoint(5., 5., 256));
			toTrans.to(ofPoint(ofRandom(256), ofRandom(256), ofRandom(256)));
			toRotate.to(ofPoint(ofRandom(TWO_PI*2.), ofRandom(TWO_PI*2.), ofRandom(TWO_PI*2.)));
			toScale.to(ofPoint(5., 5., 256));
		}
	}


private:
	ofVboMesh mesh;
	ofShader shader;

	Util::SmoothPoint fromTrans, fromRotate, fromScale;
	Util::SmoothPoint toTrans, toRotate, toScale;

	const int num = 200;
};