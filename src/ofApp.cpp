#include "ofApp.h"

using namespace yahtzee;

void ofApp::setup() {
  ofxGuiSetTextPadding(kTextPadding);

  for (int i = 0; i < category_toggles.size(); i++) {
    category_toggles[i].setup(kCategoryNames[i], false, kCategorySizeX, kCategorySizeY);
    category_toggles[i].addListener(this, &ofApp::categoryPressed);
    category_values[i].setup("", "0", kCategoryValueSize, kCategoryValueSize);
    category_values[i].setDefaultTextPadding(0);
  }
  bonus.setup("Bonus", "0/63", kCategorySizeX, kCategorySizeY);
  roll.setup("Roll [SPACE] (0/3)", kRollSizeX, kRollSizeY);
  roll.addListener(this, &ofApp::rollButtonPressed);
  score.setup("Score", "0", kScoreSizeX, kScoreSizeY);
  for (int i = 0; i < kNumDice; i++) {
    std::string keep_label = "Keep [" + std::to_string(i+1) + "]";
    keeps[i].setup(keep_label, false, kKeepSizeX, kKeepSizeY);
    keeps[i].addListener(this, &ofApp::keepTogglePressed);

    dice[i].load(GetImagePath(i + 1));
    dice[i].resize(kDieSize, kDieSize);
  }

  roll_sound.load("/sounds/diceroll.mp3");
}

void ofApp::update() {}

void ofApp::draw() {
  // drawing from top down
  for (int i  = 0; i < category_toggles.size(); i++) {
    if (i < 6) { // first 6 categories appear on first half of screen
      category_toggles[i].setPosition(0, kCategorySizeY*i);
      category_values[i].setPosition(kCategorySizeX - kCategoryValueSize, kCategoryValueSize*i);
    } else {     // last 6 categories appear on second half of screen
      category_toggles[i].setPosition(kCategorySizeX, kCategorySizeY*(i-6));
      category_values[i].setPosition(2*kCategorySizeX - kCategoryValueSize, kCategoryValueSize*(i-6));
    }
    category_toggles[i].draw();
    
    category_values[i].draw();
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
  
  std::array<int, kNumDice> dice_values = engine.GetDiceValues();
  for (int i = 0; i < kNumDice; i++) {
    dice[i].load(GetImagePath(dice_values[i]));
    dice[i].resize(kDieSize, kDieSize);
  }
  
  std::array<int, kNumCategories> cat_values = engine.GetCategoryValues();
  for (int i = 0; i < kNumCategories; i++) {
    category_values[i] = std::to_string(cat_values[i]);
  }
}

void ofApp::categoryPressed(const void* sender, bool& toggle_on) {
  if (!toggle_on) {
    return;
  }
  ofParameter<bool>* pressed = (ofParameter<bool>*)sender;
  for (auto& category: category_toggles) {
    if (category.getName() != pressed->getName()) {
      category = false;
    }
  }
}

void ofApp::keepTogglePressed(const void* sender, bool& toggle_on) {
  ofParameter<bool>* pressed = (ofParameter<bool>*)sender;
  int label_num = pressed->getName()[6] - 48; // ASCII to int conversion
  engine.ToggleKeepFlag(label_num - 1); // since the labels are 1-5
}

void ofApp::keyPressed(int key) {}

std::string ofApp::GetImagePath(int value) {
  std::string path = "images/dice.png";
  path.insert(11, std::to_string(value)); // 11 is the index of '.' in the path
  return path;
}