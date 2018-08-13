#pragma once
#include "ofFbo.h"
#include "ofShader.h"
#include "BaseProcessor.h"

class PFX {
public:
	using Ptr = std::shared_ptr<PFX>;
	PFX(const glm::vec2& size) : size(size), enabled(false) {}
	
	virtual void render(ofFbo& read, ofFbo& write) = 0;

	void setEnabled(bool enabled) { this->enabled = enabled; }
	bool getEnabled() const { return enabled; }

protected:
	const glm::vec2 size;
	bool enabled;
};

class GlitchPFX : public PFX {
public:
	GlitchPFX(const glm::vec2& size) : PFX(size) {
		shader.load("shader/vfx/passThru.vert", "shader/pfx/glitch.frag");
	}

	void render(ofFbo& read, ofFbo& write) {

		write.begin();
		ofClear(0);

		shader.begin();
		shader.setUniform1f("time", ofGetElapsedTimef());
		shader.setUniform2f("res", Constants::screenSize.x, Constants::screenSize.y);
		read.draw(0, 0);
		shader.end();

		write.end();
	}

private:
	ofShader shader;

};


class PostEffects {
public:
	using Ptr = std::shared_ptr<PostEffects>;
	PostEffects() {
		ofAddListener(ofEvents().keyPressed, this, &PostEffects::onKeyPressed);
		ofAddListener(ofEvents().keyReleased, this, &PostEffects::onKeyReleased);
	}
	~PostEffects() {
		ofRemoveListener(ofEvents().keyPressed, this, &PostEffects::onKeyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &PostEffects::onKeyReleased);
	}
	
	void onKeyPressed(ofKeyEventArgs& key) {
		if (key.key == 'a') {
			glitch->setEnabled(true);
		}
	}

	void onKeyReleased(ofKeyEventArgs& key) {
		if (key.key == 'a') {
			glitch->setEnabled(false);
		}
	}

	void init(unsigned w = ofGetWidth(), unsigned h = ofGetHeight()) {
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

		// create passes as default
		glitch = createPass<GlitchPFX>();
		
	}

	void render(ofFbo& read, bool autoDraw = false) {

		ofPushStyle();
		glPushAttrib(GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		ofSetColor(255, 255, 255);

		numProcessedPasses = 0;
		bool noEffects = true;

		for (auto& pass : passes) {
			if (pass->getEnabled()) {
				noEffects = false;

				if (numProcessedPasses == 0) pass->render(read, pingPong[1 - currentReadFbo]);
				else pass->render(pingPong[currentReadFbo], pingPong[1 - currentReadFbo]);
				currentReadFbo = 1 - currentReadFbo;
				numProcessedPasses++;
			}
		}
		
		if (noEffects) {
			pingPong[currentReadFbo].begin();
			ofClear(0);
			read.draw(0, 0);
			pingPong[currentReadFbo].end();
		}

		if (autoDraw) draw(0, 0, width, height);

		glPopAttrib();
		ofPopStyle();

	}

	void draw(float x, float y) const {
		draw(x, y, width, height);
	}

	void draw(float x, float y, float w, float h) const {
		pingPong[currentReadFbo].draw(0, 0, w, h);
	}

	float getWidth() const { return width; }
	float getHeight() const { return height; }

	template<class T>
	shared_ptr<T> createPass() {
		shared_ptr<T> pass = make_shared<T>(glm::vec2(width, height));
		passes.push_back(pass);
		return pass;
	}

	unsigned size() const { return passes.size(); }

	PFX::Ptr operator[](unsigned i) const { return passes[i]; }
	
private:
	
	unsigned currentReadFbo;
	unsigned numProcessedPasses;
	unsigned width, height;
	
	ofFbo pingPong[2];
	vector<PFX::Ptr> passes;
	
	GlitchPFX::Ptr glitch;

};