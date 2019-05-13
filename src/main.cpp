#include "ofApp.h"
#include "ofMain.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
  ofGLFWWindowSettings settings;
  settings.resizable = false;
  settings.decorated = false;
  ofCreateWindow(settings);

  // oF doesn't let you get screen size until the window is created
  int screenW = ofGetScreenWidth(); 
  int screenH = ofGetScreenHeight();
  int window_size = 0.75 * screenH;
  int xpos = (screenW - window_size) / 2;
  int ypos = (screenH - window_size) / 2;
  ofSetWindowPosition(xpos, ypos);
  ofSetWindowShape(window_size, window_size);
  return ofRunApp(new ofApp (window_size));
}
