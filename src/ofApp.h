#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "engine.h"

class ofApp : public ofBaseApp {
 public:
  ofApp(int window_size);

  // variables for GUI element sizing
  int kWindowSize;
  float kDieSize;
  float kKeepSizeX;
  float kKeepSizeY;
  float kRollSizeX;
  float kRollSizeY;
  float kScoreSizeX;
  float kScoreSizeY;
  float kCategorySizeX;
  float kCategorySizeY;
  float kCategoryValueSize;
  float kPostGameMenuSizeX;
  float kPostGameMenuSizeY;
  int kTextSize;
  int kTextPadding;

  // openFrameworks functions
  void setup();
  void update();
  void draw();
  void keyPressed(int key);

  // button listeners
  void rollButtonPressed();
  void categoryPressed(const void* sender, bool& toggle_on);
  void keepTogglePressed(const void* sender, bool& toggle_on);

  // game engine
  yahtzee::Engine engine;

  // GUI elements, top to bottom
  std::vector<ofxToggle> category_toggles;
  std::array<ofxLabel, yahtzee::kNumCategories> category_values;
  ofxLabel bonus;
  ofxButton roll;
  ofxLabel score;
  std::vector<ofxToggle> keeps;
  std::array<ofImage, yahtzee::kNumDice> dice;
  ofxLabel game_over;  // post-game menu

  // Sound effects
  ofSoundPlayer roll_sound;

 private:
  void SetupGUISizes();
  void StartNewGame();  // calls ofApp::setup() and Engine::Setup()
  std::string GetImagePath(int value);  // for locating diceX.png
  void EnableAll(std::vector<ofxToggle>& toggles);
  void EnableAllUnselected(std::vector<ofxToggle>& toggles);
  void DisableAll(std::vector<ofxToggle>& toggles);
};
