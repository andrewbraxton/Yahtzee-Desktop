#pragma once

#include "ofMain.h"

#include "ofxDatGui.h"

class ofApp : public ofBaseApp {
 public:
  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void keyReleased(int key);
  void windowResized(int w, int h);

  std::array<ofImage, 6> dice_imgs;
};
