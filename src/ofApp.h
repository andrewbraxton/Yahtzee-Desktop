#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "die.h"

class ofApp : public ofBaseApp {
 public:
  static const int kNumDice = 5;

  void setup();
  void update();
  void draw();

  void keyPressed(int key);

  // GUI elements
  std::array<ofImage, kNumDice> dice;
  std::array<ofxToggle, kNumDice> keep_toggles;
  ofxLabel bonus;
  ofxButton roll;
  ofxLabel score;

  // Sound effects
  ofSoundPlayer roll_sound;

 private:
  std::string GetImagePath(int value); // for locating dieX.png, X is 1-6 obv

};
