#pragma once
#include "Processor.hpp";

using namespace ofxDeferred;

class BaseProcessor : public ofBaseDraws {
public:
	using Ptr = std::shared_ptr<BaseProcessor>;

	void init(unsigned w = ofGetWidth(), unsigned h = ofGetHeight());

	void update(ofCamera& cam);

	void draw(float x, float y, float w, float h) const;
	float getWidth() const { return width; }
	float getHeight() const { return height; }

	template<class T>
	shared_ptr<T> createPass() {
		shared_ptr<T> pass = make_shared<T>(glm::vec2(width, height));
		passes.push_back(pass);
		return pass;
	}

	ofPtr<GBuffer> getGBuffer() { return gbuffer; }
	void setGBuffer(ofPtr<GBuffer> pGBuffer) { gbuffer = pGBuffer; }
	ofFbo& getFbo() { return pingPong[currentReadFbo]; }
	void render(bool renderFlag = false);
	void render(ofFbo& fbo);

private:
	unsigned getNumProcessedPasses() const { return numProcessedPasses; }


	unsigned currentReadFbo;
	unsigned numProcessedPasses;
	unsigned width, height;

	ofPtr<GBuffer> gbuffer;
	ofFbo pingPong[2];
	vector<RenderPass::Ptr> passes;
};
