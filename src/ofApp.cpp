#include "ofApp.h"

using namespace yahtzee;

void ofApp::setup() {
  for (int i = 0; i < score_categories.size(); i++) {
    score_categories[i].setup(kCategoryNames[i], false, kCategorySizeX, kCategorySizeY);
  }

  for (int i = 0; i < kNumDice; i++) {
    dice[i].load(GetImagePath(i + 1));
    dice[i].resize(kDieSize, kDieSize);

    std::string keep_label = "Keep [" + std::to_string(i+1) + "]";
    keeps[i].setup(keep_label, false, kKeepSizeX, kKeepSizeY);
    keeps[i].addListener(this, &ofApp::keepTogglePressed);
  }

  bonus.setup("Bonus", "0/63", kCategorySizeX, kCategorySizeY);
  roll.setup("Roll [SPACE] (0/3)", kRollSizeX, kRollSizeY);
  roll.addListener(this, &ofApp::rollButtonPressed);
  score.setup("Score", "0", kScoreSizeX, kScoreSizeY);

  roll_sound.load("/sounds/diceroll.mp3");
}

void ofApp::update() {}

void ofApp::draw() {
  ofxGuiSetTextPadding(kTextPadding);

  // drawing from top down
  for (int i  = 0; i < score_categories.size(); i++) {
    if (i < 6) { // first 6 categories appear on first half of screen
      score_categories[i].setPosition(0, kCategorySizeY*i);
    } else {     // last 6 categories appear on second half of screen
      score_categories[i].setPosition(kCategorySizeX, kCategorySizeY*(i-6));
    }
    score_categories[i].draw();
  }
  bonus.setPosition(0, kCategorySizeY * 6);
  roll.setPosition(0, kCategorySizeY * 7);
  score.setPosition(kRollSizeX, kCategorySizeY * 7);
  bonus.draw();
  roll.draw();
  score.draw();

  // drawing from bottom up
  for (int i = 0; i < kNumDice; i++) {
    dice[i].draw(kDieSize * i, kWindowSize - 0 - kDieSize);
    keeps[i].setPosition(kKeepSizeX * i, kWindowSize - 0 - kDieSize - kKeepSizeY);
    keeps[i].draw();
  }
}

void ofApp::rollButtonPressed() {
  engine.RollDice();
  std::array<int, kNumDice> values = engine.GetDiceValues();
  for (int i = 0; i < kNumDice; i++) {
    dice[i].load(GetImagePath(values[i]));
    dice[i].resize(kDieSize, kDieSize);
  }
}

void ofApp::keepTogglePressed(bool& toggle_on) {
  std::vector<bool> keep_info;
  for (auto toggle: keeps) {
    if (toggle) {
      keep_info.push_back(true);
    } else {
      keep_info.push_back(false);
    }
  }
  engine.UpdateKeepInfo(keep_info);
}

void ofApp::keyPressed(int key) {}

std::string ofApp::GetImagePath(int value) {
  std::string path = "images/dice.png";
  path.insert(11, std::to_string(value)); // 11 is the index of '.' in the path
  return path;
}