#include "BaseProcessor.h"

void BaseProcessor::init(unsigned w, unsigned h) {
	width = w;
	height = h;

	ofFbo::Settings s;
	s.width = width;
	s.height = height;
	s.internalformat = GL_RGBA;
	s.useDepth = true;
	s.useStencil = true;

	for (int i = 0; i < 2; i++) {
		pingPong[i].allocate(s);
	}

	numProcessedPasses = 0;
	currentReadFbo = 0;

}

void BaseProcessor::update(const ofCamera& cam) {

	for (auto pass : passes) {
		if (pass->getEnabled()) {
			pass->update(cam);
		}
	}

}

void BaseProcessor::draw(float x, float y, float w, float h) const {
	pingPong[currentReadFbo].draw(x, y, w, h);
}

void BaseProcessor::render(bool renderFlag) {

	ofPushStyle();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	ofSetColor(255, 255, 255);

	numProcessedPasses = 0;
	for (auto pass : passes) {
		if (pass->getEnabled()) {
			if (numProcessedPasses == 0) pass->render(gbuffer->getFbo(), pingPong[1 - currentReadFbo], *gbuffer);
			else pass->render(pingPong[currentReadFbo], pingPong[1 - currentReadFbo], *gbuffer);
			currentReadFbo = 1 - currentReadFbo;
			numProcessedPasses++;
		}

	}

	if (renderFlag) draw(0, 0, getWidth(), getHeight());
	glPopAttrib();
	ofPopStyle();

}

void BaseProcessor::render(ofFbo& fbo) {

	ofPushStyle();
	glPushAttrib(GL_ENABLE_BIT);
	glDisable(GL_LIGHTING);
	ofSetColor(255, 255, 255);

	numProcessedPasses = 0;
	for (auto pass : passes) {
		if (pass->getEnabled()) {
			if (numProcessedPasses == 0) pass->render(fbo, pingPong[1 - currentReadFbo], *gbuffer);
			else pass->render(pingPong[currentReadFbo], pingPong[1 - currentReadFbo], *gbuffer);
			currentReadFbo = 1 - currentReadFbo;
			numProcessedPasses++;
		}

	}

	draw(0, 0, getWidth(), getHeight());

	glPopAttrib();
	ofPopStyle();
}
