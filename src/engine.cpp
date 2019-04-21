#include "engine.h"

#include "ofMain.h"

using namespace yahtzee;

Engine::Engine() {
    score_ = 0;
    upper_section_score_ = 0;
    yahtzee_bonus_enabled_ = false;
}

void Engine::RollDice() {
    for (Die& die: dice_) {
        if (!die.keep) {
            die.Roll();
        }
    }
}

void Engine::UpdateKeepInfo(std::vector<bool> keep_info) {
    for (int i = 0; i < dice_.size(); i++) {
        dice_[i].keep = keep_info[i];
    }
}

std::array<int, kNumDice> Engine::GetDiceValues() {
    std::array<int, kNumDice> values;
    for (int i = 0; i < kNumDice; i++) {
        values[i] = dice_[i].value;
    }
    return values;
}

Engine::Die::Die() {
    Roll();
    keep = false;
}

void Engine::Die::Roll() {
    value = ofRandom(1, 7);
}
