#include "engine.h"

#include "ofMain.h"

#include <algorithm>

using namespace yahtzee;

Engine::Engine() {
    score_ = 0;
    upper_section_score_ = 0;
    yahtzee_bonus_enabled_ = false;
    category_values_.fill(0);
}

void Engine::RollDice() {
    for (Die& die: dice_) {
        if (!die.keep) {
            die.Roll();
        }
    }
    CalculateCategoryValues();
}

void Engine::ToggleKeepFlag(int index) {
    dice_[index].keep = !dice_[index].keep;
}

std::array<int, kNumDice> Engine::GetDiceValues() {
    std::array<int, kNumDice> values;
    for (int i = 0; i < kNumDice; i++) {
        values[i] = dice_[i].value;
    }
    return values;
}

std::array<int, kNumCategories> Engine::GetCategoryValues() {
    return category_values_;
}

Engine::Die::Die() {
    Roll();
    keep = false;
}

void Engine::Die::Roll() {
    value = ofRandom(1, 7);
}

void Engine::CalculateCategoryValues() {
    category_values_.fill(0);
    std::array<int, kMaxDieValue> dice_type_counts = CountDiceTypes();
    int dice_total = 0;
    for (int i = 0; i < kMaxDieValue; i++) { // Ones through Sixes
        category_values_[i] = dice_type_counts[i] * (i+1);
        dice_total += category_values_[i];
    }

    if (HasThreeOfAKind(dice_type_counts)) {
        category_values_[6] = dice_total;
    }
    
    if(HasFourOfAKind(dice_type_counts)) {
        category_values_[7] = dice_total;
    }

    if (HasFullHouse(dice_type_counts)) {
        category_values_[8] = kFullHouseValue;
    }

    // if (HasSmallStraight(dice_type_counts)) {
    //     category_values_[9] = kSmallStraightValue;
    // }

    // if (HasLargeStraight(dice_type_counts)) {
    //     category_values_[10] = kLargeStraightValue;
    // }

    if(HasYahtzee(dice_type_counts)) {
        category_values_[11] = kYahtzeeValue;
    }

    category_values_[12] = dice_total; // Chance
}

std::array<int, kMaxDieValue> Engine::CountDiceTypes() {
    std::array<int, kMaxDieValue> dice_type_counts;
    dice_type_counts.fill(0);
    for (int i = 0; i < kNumDice; i++) {
        int val = dice_[i].value;
        dice_type_counts[val - 1]++;
    }
    return dice_type_counts;
}

bool Engine::HasThreeOfAKind(std::array<int, kMaxDieValue> counts) {
    return std::any_of(counts.begin(), counts.end(), [](int i){return i>=3;});
}

bool Engine::HasFourOfAKind(std::array<int, kMaxDieValue> counts) {
    return std::any_of(counts.begin(), counts.end(), [](int i){return i>=4;});
    //return *(std::max_element(counts.begin(), counts.end())) >= 4;
}

bool Engine::HasFullHouse(std::array<int, kMaxDieValue> counts) {
    return HasThreeOfAKind(counts) && std::any_of(counts.begin(), counts.end(), [](int i){return i==2;});
}

bool Engine::HasYahtzee(std::array<int, kMaxDieValue> counts) {
    return std::any_of(counts.begin(), counts.end(), [](int i){return i==5;});
}
