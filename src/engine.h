#pragma once

#include <array>
#include <vector>

namespace yahtzee {

const int kNumDice = 5;
const int kNumCategories = 13;
const int kUpperSectionBonusThreshold = 63;
const int UpperSectionBonusValue = 35;
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
        std::array<int, 6> CountDiceTypes();
        bool HasThreeOfAKind(std::array<int, 6> dice_type_counts);
        bool HasFourOfAKind(std::array<int, 6> dice_type_counts);
        bool HasYahtzee(std::array<int, 6> dice_type_counts);
        //int CalculateTotalDiceValue();

        int score_;
        int upper_section_score_;
        bool yahtzee_bonus_enabled_;
        std::array<Die, kNumDice> dice_;
        std::array<int, kNumCategories> category_values_;
};

}