#include "ofApp.h"

using namespace yahtzee;

void ofApp::setup() {
  for (int i = 0; i < kNumDice; i++) {
    dice[i].load(GetImagePath(i + 1));
    dice[i].resize(kDrawInterval, kDrawInterval);
    keep_toggles[i].setup("Keep", false, kDrawInterval, kElementHeight);
  }
  bonus.setup("Bonus", "0/63", kWindowSize / 4, kElementHeight);
  roll.setup("Roll (0/3)", kWindowSize / 2, kElementHeight);
  score.setup("Score", "0", kWindowSize / 4, kElementHeight);

  roll_sound.load("/sounds/diceroll.mp3");
}

void ofApp::update() {}

void ofApp::draw() {
  for (int i = 0; i < kNumDice; i++) {
    dice[i].draw(kDrawInterval * i, kWindowSize - kDrawInterval);
    keep_toggles[i].setPosition(kDrawInterval * i, kWindowSize - kDrawInterval - kElementHeight);
    keep_toggles[i].draw();
  }

  bonus.setPosition(0, kWindowSize - kDrawInterval - 2*kElementHeight);
  roll.setPosition(kWindowSize / 4, kWindowSize - kDrawInterval - 2*kElementHeight);
  score.setPosition(kWindowSize * 3/4, kWindowSize - kDrawInterval - 2*kElementHeight);

  bonus.draw();
  roll.draw();
  score.draw();
}

void ofApp::keyPressed(int key) {}

std::string ofApp::GetImagePath(int value) {
  std::string path = "images/dice.png";
  path.insert(11, std::to_string(value)); // 11 is the index of '.' in the path
  return path;
}