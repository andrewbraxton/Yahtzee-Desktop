#include "ofApp.h"

//#include <iostream>

using namespace yahtzee;

void ofApp::setup() {
  int xinterval = ofGetWidth() / kNumDice;
  int yinterval = ofGetHeight() / kNumDice;
  int element_height = 75;

  for (int i = 0; i < kNumDice; i++) {
    dice[i].Setup(xinterval, yinterval);
    dice[i].SetPosition(xinterval * i, ofGetHeight() - yinterval);
    keep_toggles[i].setup("Keep", false, xinterval, element_height);
    keep_toggles[i].setPosition(xinterval * i, ofGetHeight() - yinterval - element_height);
  }

  bonus.setup("Bonus", "0/63", ofGetWidth() / 4, element_height);
  bonus.setPosition(0, ofGetHeight() - yinterval - element_height - element_height);
  roll.setup("Roll (0/3)", ofGetWidth() / 2, element_height);
  roll.setPosition(ofGetWidth() / 4, ofGetHeight() - yinterval - element_height - element_height);
  score.setup("Score", "0", ofGetWidth() / 4, element_height);
  score.setPosition(ofGetWidth() * 3 / 4, ofGetHeight() - yinterval - element_height - element_height);

  roll_sound.load("/sounds/diceroll.mp3");
}



void ofApp::update() {}

void ofApp::draw() {
  for (int i = 0; i < kNumDice; i++) {
    dice[i].Draw();
    keep_toggles[i].draw();
  }

  bonus.draw();
  roll.draw();
  score.draw();
}

void ofApp::keyPressed(int key) {}

void ofApp::keyReleased(int key) {}

void ofApp::windowResized(int w, int h) {}