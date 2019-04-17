#include "ofApp.h"

//#include <iostream>

using namespace yahtzee;

void ofApp::setup() {
  roll_sound.load("/sounds/diceroll.mp3");

  int xinterval = ofGetWidth() / kNumDice;
  int yinterval = ofGetHeight() / kNumDice;
  for (int i = 0; i < kNumDice; i++) {
    dice[i].Setup(xinterval, yinterval);
    dice[i].SetPosition(xinterval * i, ofGetHeight() - yinterval);
    keep_toggles[i].setup("Keep", false, xinterval, 50);
    keep_toggles[i].setPosition(xinterval * i, ofGetHeight() - yinterval - 50);
  }
}

void ofApp::update() {}

void ofApp::draw() {
  for (int i = 0; i < kNumDice; i++) {
    dice[i].Draw();
    keep_toggles[i].draw();
  }
}

void ofApp::keyPressed(int key) {}

void ofApp::keyReleased(int key) {}

void ofApp::windowResized(int w, int h) {}