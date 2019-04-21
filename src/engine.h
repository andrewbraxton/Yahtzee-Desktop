#pragma once

#include <array>
#include <vector>

namespace yahtzee {

const int kNumDice = 5;
const int kNumCategories = 13;
const int kUpperSectionBonusThreshold = 63;

class Engine {

    public:
        Engine();

        void RollDice();
        void UpdateKeepInfo(std::vector<bool> keep_info);
        std::array<int, kNumDice> GetDiceValues();
    private:
        struct Die {
            Die();
            void Roll();
            int value;
            bool keep;
        };

        enum Categories {
            ONES,
            TWOS,
            THREES,
            FOURS,
            FIVES,
            SIXES,
            THREE_OF_A_KIND,
            FOUR_OF_A_KIND,
            FULL_HOUSE,
            SMALL_STRAIGHT,
            LARGE_STRAIGHT,
            YAHTZEE,
            CHANCE
        };

        int score_;
        int upper_section_score_;
        bool yahtzee_bonus_enabled_;
        std::array<Die, kNumDice> dice_;
        //std::array<std::pair<Category, value>, kNumCategories> category_values_;

};

}