#include "engine.h"

#include "ofMain.h"

using namespace yahtzee;

Engine::Die::Die() {
    Roll();
}

void Engine::Die::Roll() {
    int dice_roll = ofRandom(1,7);
    value_ = dice_roll;
}