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
  void keyReleased(int key);
  void windowResized(int w, int h);

  std::array<yahtzee::Die, kNumDice> dice;

  std::array<ofxToggle, kNumDice> keep_toggles;

  ofSoundPlayer roll_sound;
};
