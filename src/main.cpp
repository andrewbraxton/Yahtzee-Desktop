#include "ofApp.h"
#include "ofMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
  ofGLFWWindowSettings settings;
  settings.setSize(ofApp::kWindowSize, ofApp::kWindowSize);
  settings.resizable = false;
  settings.decorated = false;
  ofCreateWindow(settings);
  int xpos = (ofGetScreenWidth() - ofApp::kWindowSize) / 2;
  int ypos = (ofGetScreenHeight() - ofApp::kWindowSize) / 2;
  ofSetWindowPosition(xpos, ypos);
  return ofRunApp(new ofApp);
}
