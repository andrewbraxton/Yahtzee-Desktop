#include "ofMain.h"
#include "ofApp.h"

int main( ){
	ofGLFWWindowSettings settings;
	settings.setSize(1460, 1340);
	settings.resizable = false;
	ofCreateWindow(settings);
	return ofRunApp(new ofApp);
}
