#include "ofMain.h"
#include "ofApp.h"
#include "SimulatorApp.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings s;
	s.setGLVersion(4, 1);

	if (ofApp::mode == ofApp::PRODUCTION) {
		
		s.setSize(Constants::screenSize.x * 2, Constants::screenSize.y);
		s.setPosition(glm::vec2(Constants::screenSize.x, 0));
		s.decorated = false;
		s.multiMonitorFullScreen = true;
		
		ofCreateWindow(s);
		ofRunApp(new ofApp());

	} else if (ofApp::mode == ofApp::SANDBOX) {
		
		s.setSize(Constants::screenSize.x / 2, Constants::screenSize.y / 2);
		
		ofPtr<ofAppBaseWindow> mainWindow = ofCreateWindow(s);
		
		s.setSize(1024, 768);
		s.shareContextWith = mainWindow;
		ofPtr<ofAppBaseWindow> simWindow = ofCreateWindow(s);

		shared_ptr<ofApp> mainApp(new ofApp());
		shared_ptr<SimulatorApp> simApp(new SimulatorApp);
		simApp->mainApp = mainApp;
		
		ofRunApp(mainWindow, mainApp);
		ofRunApp(simWindow, simApp);

		ofRunMainLoop();
		
	}	

}
