#pragma once

#include "ofMain.h"
#include "ofxGui.h"

#include "engine.h"

class ofApp : public ofBaseApp {
 public:

  static const int kWindowSize = 1635;
  const float kDieSize = 0.20 * kWindowSize;
  const float kKeepSizeX = kDieSize;
  const float kKeepSizeY = 0.05 * kWindowSize;
  const float kRollSizeX = 0.75 * kWindowSize;
  const float kRollSizeY = 0.05 * kWindowSize;
  const float kScoreSizeX = kWindowSize - kRollSizeX;
  const float kScoreSizeY = kRollSizeY;
  const float kCategorySizeX = 0.50 * kWindowSize;
  const float kCategorySizeY = 0.10 * kWindowSize;
  const int kTextPadding = 30;

  const std::array<std::string, 13> kCategoryNames =
    {
        "Ones",
        "Twos",
        "Threes",
        "Fours",
        "Fives",
        "Sixes",
        "Three of a Kind",
        "Four of a Kind",
        "Full House",
        "Small Straight",
        "Large Straight",
        "Yahtzee!",
        "Chance"
    };

  void setup();
  void update();
  void draw();

  void keyPressed(int key);
  void rollButtonPressed();
  //void keepTogglePressed(bool& toggle_on);

  yahtzee::Engine engine;

  // GUI elements
  std::array<ofImage, yahtzee::kNumDice> dice;
  std::array<ofxToggle, yahtzee::kNumDice> keeps;
  ofxLabel bonus;
  ofxButton roll;
  ofxLabel score;
  std::array<ofxToggle, yahtzee::kNumCategories> score_categories;

  // Sound effects
  ofSoundPlayer roll_sound;

 private:
  std::string GetImagePath(int value); // for locating diceX.png, X is 1-6 obv

};
