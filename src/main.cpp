#include "ofMain.h"
#include "ofApp.h"
#include "SimulatorApp.h"

//========================================================================
int main( ){

	ofGLFWWindowSettings s;
	
	// main
	s.setGLVersion(4, 1);
	if (ofApp::mode == ofApp::PRODUCTION) {
		
		s.setSize(1920 * 2, 1080);
		s.setPosition(glm::vec2(1921, 0));
		s.decorated = false;
		s.multiMonitorFullScreen = true;
		
		ofCreateWindow(s);
		ofRunApp(new ofApp());

	} else if (ofApp::mode == ofApp::SANDBOX) {
		
		s.setSize(1920, 540);
		
		ofPtr<ofAppBaseWindow> mainWindow = ofCreateWindow(s);
		
		s.setSize(1024, 768);
		s.shareContextWith = mainWindow;
		ofPtr<ofAppBaseWindow> simWindow = ofCreateWindow(s);

		shared_ptr<ofApp> mainApp(new ofApp);
		shared_ptr<SimulatorApp> simApp(new SimulatorApp);
		simApp->mainApp = mainApp;
		
		ofRunApp(mainWindow, mainApp);
		ofRunApp(simWindow, simApp);

		ofRunMainLoop();
		
	}	

}
