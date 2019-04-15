#include "ofApp.h"

void ofApp::setup() {

  for (int i = 0; i < dice_imgs.size(); i++) {
    std::string img_name = "images/dice.png";
    img_name.insert(11, to_string(i+1));
    dice_imgs[i].load(img_name);
  }
}

void ofApp::update() { 
}

void ofApp::draw() { 

  int xinterval = ofGetWidth() / 6;
  int yinterval = ofGetHeight() / 6;
  for (int i = 0; i < dice_imgs.size(); i++) {
    dice_imgs[i].draw(xinterval * i, ofGetHeight() - yinterval, xinterval, yinterval);
  }
}

void ofApp::keyPressed(int key) { }

void ofApp::keyReleased(int key) {}

void ofApp::windowResized(int w, int h) {}