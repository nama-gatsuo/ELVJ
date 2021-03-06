#pragma once
#include "BaseLayer.h"
#include "ofxDeferredShading.h"
#include "BaseProcessor.h"
#include "BaseWorld.h"

using namespace ofxDeferred;

class ThreeLayer : public BaseLayer {
public:
	ThreeLayer(const glm::ivec2& size, int id) : BaseLayer(size, id) {
		processor.init(size.x, size.y);
	}

	virtual const ofFbo& getFbo() const { return processor.getFbo(); }
	
	void draw() const {
		getFbo().draw(0, 0);
	}

	virtual void render() {
		processor.update(world->getCam());
		processor.render();
	}

	void setWorld(ofPtr<BaseWorld> world) {
		this->world = world;
		processor.setGBuffer(world->getGBufferPointer());
	}

	void bang(int& id) {}

protected:
	BaseProcessor processor;
	ofPtr<BaseWorld> world; // 3d objects to share in ThreeLayer
};

// edge detection 3D layer
class EdgeThreeLayer : public ThreeLayer {
public:
	EdgeThreeLayer(const glm::ivec2& size, int id) : ThreeLayer(size, id) {
		ofFloatColor pink;
		pink.setHex(0xfd637c);

		edge = processor.createPass<EdgePass>();
		edge->setEdgeColor(pink);
		edge->setBackground(ofFloatColor(.0));
		edge->setUseReadColor(false);
	}

	void render() {
		ThreeLayer::render();
	}

private:
	EdgePass::Ptr edge;
};

// photo realistc 3D layer
class PRThreeLayer : public ThreeLayer {
public:
	PRThreeLayer(const glm::ivec2& size, int id) : ThreeLayer(size, id) {
		auto sh = processor.createPass<ShadowLightPass>();
		sh->setAmbientColor(ofFloatColor(0.1));
		sh->setDiffuseColor(ofFloatColor(0.4, 0.5, 0.5));
		sh->setDarkness(0.5);
		sh->setDistance(400);
		sh->setDirection(glm::vec3(1., -1., -1.5));
		sh->setFar(768);

		auto s = processor.createPass<SsaoPass>();
		s->setDarkness(.5);
		s->setOcculusionRadius(1.);

		processor.createPass<HdrBloomPass>();
	
		auto d = processor.createPass<DofPass>();
		d->setAperture(0.02);
		d->setFocus(0.1);
		d->setMaxBlur(0.1);
	}
};

class SimpleThreeLayer : public ThreeLayer {
public:
	SimpleThreeLayer(const glm::ivec2& size, int id) : ThreeLayer(size, id) {
		processor.createPass<HdrBloomPass>();

		//auto d = processor.createPass<DofPass>();
		//d->setAperture(0.02);
		//d->setFocus(0.1);
		//d->setMaxBlur(0.1);
	}

	void render() {
		ThreeLayer::render();
	}

private:
	
};