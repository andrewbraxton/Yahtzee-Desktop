#include "engine.h"

#include "ofMain.h"

#include <algorithm>

using namespace yahtzee;

Engine::Engine() {
    Setup();
}

void Engine::Setup() {
    state_ = PRE_GAME;
    round_number_ = 1;
    roll_number_ = 0;
    score_ = 0;
    upper_section_score_ = 0;
    upper_section_bonus_earned_ = false;
    yahtzee_bonus_enabled_ = false;
    yahtzee_category_filled_ = false;
    category_values_.fill(0);
}

void Engine::RollDice() {
    roll_number_++;
    if (roll_number_ == 3) {
        state_ = END_ROUND;
    } else {
        state_ = MID_ROUND;
    }

    for (Die& die: dice_) {
        if (!die.keep) {
            die.Roll();
        }
    }
    CalculateCategoryValues();
}

void Engine::UpdateKeepFlag(int index, bool keep) {
    dice_[index].keep = keep;
}

GameStates Engine::GetGameState() {
    return state_;
}

int Engine::GetRollNumber() {
    return roll_number_;
}

int Engine::GetScore() {
    return score_;
}

int Engine::GetUpperSectionScore() {
    return upper_section_score_;
}

std::array<int, kNumDice> Engine::GetDiceValues() {
    std::array<int, kNumDice> values;
    for (int i = 0; i < kNumDice; i++) {
        values[i] = dice_[i].value;
    }
    return values;
}

void Engine::AddCategoryValueToScore(int index) {
    roll_number_ = 0;
    if (round_number_ == kNumCategories) {
        state_ = END_GAME;
    } else {
        round_number_++;
        state_ = BETWEEN_ROUNDS;
    }

    int value = category_values_[index];
    score_ += value;
    if (index < 6) {
        upper_section_score_ += value;
    }
    if (!upper_section_bonus_earned_ && upper_section_score_ >= kUpperSectionBonusThreshold) {
        score_ += kUpperSectionBonusValue;
        upper_section_bonus_earned_ = true;
    }

    if (index == 11) {
        if (category_values_[index] > 0) {
            yahtzee_bonus_enabled_ = true;
        }
        yahtzee_category_filled_ = true;
    }
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
    std::array<int, kMaxDieValue> counts = CountDiceTypes();
    int dice_total = 0;

    for (int i = 0; i < kMaxDieValue; i++) {
        category_values_[i] = counts[i] * (i+1); // Ones through Sixes
        dice_total += category_values_[i];
    }
    if (HasThreeOfAKind(counts)) category_values_[6] = dice_total;
    if (HasFourOfAKind(counts)) category_values_[7] = dice_total;
    if (HasFullHouse(counts)) category_values_[8] = kFullHouseValue;
    if (HasSmallStraight(counts)) category_values_[9] = kSmallStraightValue;
    if (HasLargeStraight(counts)) category_values_[10] = kLargeStraightValue;
    if (HasYahtzee(counts)) HandleYahtzee(dice_total);
    category_values_[12] = dice_total;          // Chance
}

std::array<int, kMaxDieValue> Engine::CountDiceTypes() {
    std::array<int, kMaxDieValue> counts;
    counts.fill(0);
    for (int i = 0; i < kNumDice; i++) {
        int val = dice_[i].value;
        counts[val - 1]++;
    }
    return counts;
}

bool Engine::HasThreeOfAKind(std::array<int, kMaxDieValue> counts) {
    return std::any_of(counts.begin(), counts.end(), [](int i){return i>=3;});
}

bool Engine::HasFourOfAKind(std::array<int, kMaxDieValue> counts) {
    return std::any_of(counts.begin(), counts.end(), [](int i){return i>=4;});
}

bool Engine::HasFullHouse(std::array<int, kMaxDieValue> counts) {
    return HasThreeOfAKind(counts) &&
           std::any_of(counts.begin(), counts.end(), [](int i){return i==2;});
}

bool Engine::HasSmallStraight(std::array<int, kMaxDieValue> counts) {
    return CalculateLongestStraight(counts) >= 4;
}

bool Engine::HasLargeStraight(std::array<int, kMaxDieValue> counts) {
    return CalculateLongestStraight(counts) == 5;
}

bool Engine::HasYahtzee(std::array<int, kMaxDieValue> counts) {
    return std::any_of(counts.begin(), counts.end(), [](int i){return i==5;});
}

int Engine::CalculateLongestStraight(std::array<int, kMaxDieValue> counts) {
    int longest = 0;
    int temp = 0;
    for (int count: counts) {
        if (count > 0) {
            temp++;
            if (temp > longest) {
                longest = temp;
            }
        } else {
            temp = 0;
        }
    }
    return longest;
}

void Engine::HandleYahtzee(int dice_total) {
    if (yahtzee_bonus_enabled_) score_ += kYahtzeeBonusValue;
    if (yahtzee_category_filled_) {
        category_values_[6] = dice_total;
        category_values_[7] = dice_total;
        category_values_[8] = kFullHouseValue;
        category_values_[9] = kSmallStraightValue;
        category_values_[10] = kLargeStraightValue;
    }
    category_values_[11] = kYahtzeeValue;
}

bool Engine::UpperSectionBonusEarned() {
    return upper_section_bonus_earned_;
}