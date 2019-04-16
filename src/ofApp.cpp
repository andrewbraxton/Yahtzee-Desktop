#include "ofApp.h"

//#include <iostream>

using namespace yahtzee;

void ofApp::setup() {
  roll_sound.load("/sounds/diceroll.mp3");
}

void ofApp::update() { 
}

void ofApp::draw() {
  int xinterval = ofGetWidth() / kNumDice;
  int yinterval = ofGetHeight() / kNumDice;
   for (int i = 0; i < kNumDice; i++) {
     dice[i].Draw(xinterval * i, ofGetHeight() - yinterval, xinterval, yinterval);
     keep_toggles[i].setup("Keep", true, xinterval, 50);
     keep_toggles[i].setPosition(xinterval * i, ofGetHeight() - yinterval - 50);
     keep_toggles[i].draw();
   }
}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {}

void ofApp::windowResized(int w, int h) {}