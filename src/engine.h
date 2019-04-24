#pragma once

#include <array>
#include <vector>

namespace yahtzee {

const int kMaxDieValue = 6;
const int kNumDice = 5;
const int kNumCategories = 13;
const int kUpperSectionBonusThreshold = 63;
const int kUpperSectionBonusValue = 35;
const int kFullHouseValue = 25;
const int kSmallStraightValue = 30;
const int kLargeStraightValue = 40;
const int kYahtzeeValue = 50;
const int kYahtzeeBonusValue = 100;
const std::array<std::string, kNumCategories> kCategoryNames =
    {
        "Ones",
        "Twos",
        "Threes",
        "Fours",
        "Fives",
        "Sixes",
        "Three of a Kind",
        "Four of a Kind",
        "Full House",
        "Small Straight",
        "Large Straight",
        "Yahtzee!",
        "Chance"
    };

class Engine {

    public:
        Engine();

        void RollDice();
        void ToggleKeepFlag(int index);
        void AddCategoryValueToScore(int index);

        int GetScore();
        int GetUpperSectionScore();
        std::array<int, kNumDice> GetDiceValues();
        std::array<int, kNumCategories> GetCategoryValues();
    private:
        struct Die {
            Die();
            void Roll();
            int value;
            bool keep;
        };

        void CalculateCategoryValues();
        std::array<int, kMaxDieValue> CountDiceTypes();
        
        bool HasThreeOfAKind(std::array<int, kMaxDieValue> dice_type_counts);
        bool HasFourOfAKind(std::array<int, kMaxDieValue> dice_type_counts);
        bool HasFullHouse(std::array<int, kMaxDieValue> dice_type_counts);
        int CalculateLongestStraight(std::array<int, kMaxDieValue> dice_type_counts);
        bool HasSmallStraight(std::array<int, kMaxDieValue> dice_type_counts);
        bool HasLargeStraight(std::array<int, kMaxDieValue> dice_type_counts);
        bool HasYahtzee(std::array<int, kMaxDieValue> dice_type_counts);

        int score_;
        int upper_section_score_;
        bool upper_section_bonus_earned_;
        bool yahtzee_bonus_enabled_;
        std::array<Die, kNumDice> dice_;
        std::array<int, kNumCategories> category_values_;
};

}