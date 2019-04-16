#include "ofApp.h"

#include <iostream>

using namespace yahtzee;

void ofApp::setup() {
  for (int i = 0; i < dice.size(); i++) {
    dice[i] = Die();
  }

  roll_sound.load("/sounds/diceroll.mp3");
}

void ofApp::update() { 
}

void ofApp::draw() { 
  int xinterval = ofGetWidth() / 6;
  int yinterval = ofGetHeight() / 6;
   for (int i = 0; i < dice.size(); i++) {
     dice[i].Draw(xinterval * i, ofGetHeight() - yinterval, xinterval, yinterval);
   }
}

void ofApp::keyPressed(int key) {
}

void ofApp::keyReleased(int key) {}

void ofApp::windowResized(int w, int h) {}