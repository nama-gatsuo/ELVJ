#include "ThreeLayer.h"

ofPtr<ofxDeferred::GBuffer> ThreeLayer::gbuffer;
ofPtr<ofEasyCam> ThreeLayer::cam;

ThreeLayer::ThreeLayer(int w, int h) : BaseLayer(w, h) {
	if (gbuffer == nullptr) {
		gbuffer = std::make_shared<ofxDeferred::GBuffer>();
		gbuffer->setup(w, h);
	}

	if (cam == nullptr) {
		cam = std::make_shared<ofEasyCam>();
	}

	processor.init(w, h);
	processor.setGBuffer(gbuffer);

	auto s = processor.createPass<SsaoPass>();
	s->setDarkness(1.);
	s->setOcculusionRadius(1.);
	processor.createPass<HdrBloomPass>();

}

void ThreeLayer::render() {
	gbuffer->begin(*cam);
	for (auto& obj : objects) {
		obj->update();
		obj->draw(1. / (cam->getFarClip() - cam->getNearClip()));
	}
	gbuffer->end();

	processor.update(*cam);
	processor.render();
}