#include "ofApp.h"

using namespace yahtzee;

void ofApp::setup() {
  ofxGuiSetTextPadding(kTextPadding);

  // setup category toggles and value labels
  for (int i = 0; i < category_toggles.size(); i++) {
    category_toggles[i].setup(kCategoryNames[i], false, kCategorySizeX, kCategorySizeY);
    category_toggles[i].addListener(this, &ofApp::categoryPressed);
    category_values[i].setup("", "0", kCategoryValueSize, kCategoryValueSize);
  }

  // setup bonus, roll, and score elements
  bonus.setup("Bonus", "0/63", kCategorySizeX, kCategorySizeY);
  roll.setup("Roll [SPACE] (0/3)", kRollSizeX, kRollSizeY);
  roll.addListener(this, &ofApp::rollButtonPressed);
  score.setup("Score", "0", kScoreSizeX, kScoreSizeY);

  // setup keep toggles and dice images
  for (int i = 0; i < kNumDice; i++) {
    std::string keep_label = "Keep [" + std::to_string(i+1) + "]";
    keeps[i].setup(keep_label, false, kKeepSizeX, kKeepSizeY);
    keeps[i].addListener(this, &ofApp::keepTogglePressed);

    dice[i].load(GetImagePath(i + 1));
    dice[i].resize(kDieSize, kDieSize);
  }

  roll_sound.load("/sounds/diceroll.mp3");
}

void ofApp::update() {
  switch (engine.GetGameState()) {
    // disable everything except roll
    case PRE_GAME:
        roll.registerMouseEvents();
        std::for_each(category_toggles.begin(), category_toggles.end(), [](auto& i) {i.unregisterMouseEvents();});
        std::for_each(keeps.begin(), keeps.end(), [](auto& i) {i.unregisterMouseEvents();});
        break;
    // enable everything except selected categories
    case MID_ROUND:
        roll.registerMouseEvents();
        std::for_each(category_toggles.begin(), category_toggles.end(), [](auto& i) {if(!i) i.registerMouseEvents();});
        std::for_each(keeps.begin(), keeps.end(), [](auto& i) {i.registerMouseEvents();});
        break;
    // disable everything except unselected categories
    case END_ROUND:
        roll.unregisterMouseEvents();
        std::for_each(category_toggles.begin(), category_toggles.end(), [](auto& i) {if(!i) i.registerMouseEvents();});
        std::for_each(keeps.begin(), keeps.end(), [](auto& i) {i.unregisterMouseEvents();});
        break;
    // disable everything except roll and turn off keep toggles
    case BETWEEN_ROUNDS:
        roll.registerMouseEvents();
        std::for_each(category_toggles.begin(), category_toggles.end(), [](auto& i) {i.unregisterMouseEvents();});
        std::for_each(keeps.begin(), keeps.end(), [](auto& i) {i = false; i.unregisterMouseEvents();});
        break;
    // disable everything
    case END_GAME:
        roll.unregisterMouseEvents();
        std::for_each(category_toggles.begin(), category_toggles.end(), [](auto& i) {i.unregisterMouseEvents();});
        std::for_each(keeps.begin(), keeps.end(), [](auto& i) {i.unregisterMouseEvents();});
        break;
    // should not reach
    default:
        assert(false);
  }
}

void ofApp::draw() {
  // draw from top down
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

  // draw from bottom up
  for (int i = 0; i < kNumDice; i++) {
    dice[i].draw(kDieSize * i, kWindowSize - 0 - kDieSize);
    keeps[i].setPosition(kKeepSizeX * i, kWindowSize - 0 - kDieSize - kKeepSizeY);
    keeps[i].draw();
  }
}

void ofApp::rollButtonPressed() {
  engine.RollDice();
  
  // update the dice images
  std::array<int, kNumDice> dice_values = engine.GetDiceValues();
  for (int i = 0; i < kNumDice; i++) {
    dice[i].load(GetImagePath(dice_values[i]));
    dice[i].resize(kDieSize, kDieSize);
  }
  
  // update the category value labels for non-selected categories
  std::array<int, kNumCategories> cat_values = engine.GetCategoryValues();
  for (int i = 0; i < kNumCategories; i++) {
    if (!category_toggles[i]) {
      category_values[i] = std::to_string(cat_values[i]);
    }
  }

  // update the name of the roll button
  std::string roll_number = std::to_string(engine.GetRollNumber());
  roll.setName("Roll [SPACE] (" + roll_number + "/3)");

  roll_sound.play();
}

void ofApp::categoryPressed(const void* sender, bool& toggle_on) {
  // find and send the index of the selected category to the engine
  ofParameter<bool>* pressed = (ofParameter<bool>*)sender;
  for (int i = 0; i < kNumCategories; i++) {
    if (category_toggles[i].getName() == pressed->getName()) {
      engine.AddCategoryValueToScore(i);
      break;
    }
  }

  // update the name of the roll button
  roll.setName("Roll [SPACE] (0/3)");

  // update the score and bonus labels
  int upper_section_score = engine.GetUpperSectionScore();
  if (upper_section_score >= kUpperSectionBonusThreshold) {
    bonus = "Earned";
  } else {
    bonus = std::to_string(engine.GetUpperSectionScore()) + "/63";
  }
  score = std::to_string(engine.GetScore());
}

void ofApp::keepTogglePressed(const void* sender, bool& toggle_on) {
  ofParameter<bool>* pressed = (ofParameter<bool>*)sender;
  int label_num = pressed->getName()[6] - 48; // ASCII to int conversion
  engine.UpdateKeepFlag(label_num - 1, toggle_on); // since the labels are 1-5
}

void ofApp::keyPressed(int key) {
  // GameStates state = engine.GetGameState();
  // int roll_number = engine.GetRollNumber();
  // if(state == END_GAME || roll_number == 3) {
  //   return;
  // } else if (key == ' ') {
  //   rollButtonPressed();
  // } else if (state == MID_GAME && roll_number != 0 && key >= '1' && key <= '5') {
  //   keeps[key-48-1] = !keeps[key-48-1]; // ASCII to int conversion, -1 for index
  // }
}

std::string ofApp::GetImagePath(int value) {
  std::string path = "images/dice.png";
  path.insert(11, std::to_string(value)); // 11 is the index of '.' in the path
  return path;
}