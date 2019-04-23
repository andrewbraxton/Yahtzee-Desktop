#pragma once

#include <array>
#include <vector>
#include <map>

namespace yahtzee {

const int kNumDice = 5;
const int kNumCategories = 13;
const int kUpperSectionBonusThreshold = 63;
const std::array<std::string, 13> kCategoryNames =
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
    private:
        struct Die {
            Die();
            void Roll();
            int value;
            bool keep;
        };

        int score_;
        int upper_section_score_;
        bool yahtzee_bonus_enabled_;
        std::array<Die, kNumDice> dice_;
        std::map<std::string, int> category_values_;
};

}