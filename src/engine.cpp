#include "engine.h"

#include "ofMain.h"

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
    std::map<int, int> dice_type_counts = CountDiceTypes();
    int dice_total = 0;
    for (int i = 0; i < kNumCategories; i++) { // Ones through Sixes
        category_values_[i] = dice_type_counts[i+1] * i+1;
        dice_total += category_values_[i];
    }

    if (HasThreeOfAKind(dice_type_counts)) {
        category_values_[6] = dice_total;
    }
    
    if(HasFourOfAKind(dice_type_counts)) {
        category_values_[7] = dice_total;
    }

    // if (HasFullHouse(dice_type_counts)) {
    //     category_values_[8] = kFullHouseValue;
    // }

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

std::map<int, int> Engine::CountDiceTypes() {
    std::map<int, int> dice_type_counts;
    for (Die d: dice_) {
        dice_type_counts[d.value]++;
    }
    return dice_type_counts;
}

bool Engine::HasThreeOfAKind(std::map<int, int> dice_type_counts) {
    return dice_type_counts.find(3) != dice_type_counts.end() || HasFourOfAKind(dice_type_counts);
}

bool Engine::HasFourOfAKind(std::map<int, int> dice_type_counts) {
    return dice_type_counts.find(4) != dice_type_counts.end() || HasYahtzee(dice_type_counts);
}

bool Engine::HasYahtzee(std::map<int, int> dice_type_counts) {
    return dice_type_counts.find(5) != dice_type_counts.end();
}

// int Engine::CalculateTotalDiceValue() {
//     int total = 0;
//     for (Die d: dice_) {
//         total += dice_.value;
//     }
//     return total;
// }