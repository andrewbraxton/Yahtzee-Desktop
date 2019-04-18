#include "ofMain.h"
#include "ofApp.h"

int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(ofApp::kWindowSize, ofApp::kWindowSize);
	settings.resizable = false;
	ofCreateWindow(settings);
	return ofRunApp(new ofApp);
}
