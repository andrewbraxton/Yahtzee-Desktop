#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "engine.h"

class ofApp : public ofBaseApp {
 public:

  static const int kWindowSize = 1600;
  const float kDieSize = 0.20 * kWindowSize;
  const float kKeepSizeX = kDieSize;
  const float kKeepSizeY = 0.05 * kWindowSize;
  const float kRollSizeX = 0.75 * kWindowSize;
  const float kRollSizeY = 0.05 * kWindowSize;
  const float kScoreSizeX = kWindowSize - kRollSizeX;
  const float kScoreSizeY = kRollSizeY;
  const float kCategorySizeX = 0.50 * kWindowSize;
  const float kCategorySizeY = 0.10 * kWindowSize;
  const float kCategoryValueSize = kCategorySizeY;
  const float kPostGameMenuSizeX = 0.80 * kWindowSize;
  const float kPostGameMenuSizeY = 0.20 * kWindowSize;
  const int kTextSize = 20;
  const int kTextPadding = 30;

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void rollButtonPressed();
  void categoryPressed(const void* sender, bool& toggle_on);
  void keepTogglePressed(const void* sender, bool& toggle_on);

  yahtzee::Engine engine;

  // GUI elements, top to bottom
  std::array<ofxToggle, yahtzee::kNumCategories> category_toggles;
  std::array<ofxLabel, yahtzee::kNumCategories> category_values;
  ofxLabel bonus;
  ofxButton roll;
  ofxLabel score;
  std::array<ofxToggle, yahtzee::kNumDice> keeps;
  std::array<ofImage, yahtzee::kNumDice> dice;
  ofxLabel game_over; // post-game menu
  
  // Sound effects
  ofSoundPlayer roll_sound;

 private:
  void StartNewGame();
  std::string GetImagePath(int value); // for locating diceX.png, X is 1-6 obv

};
