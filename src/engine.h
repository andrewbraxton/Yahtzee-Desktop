#pragma once

#include <array>
#include <vector>
#include <string>

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
const std::array<std::string, kNumCategories> kCategoryNames = {
    "Ones",       "Twos",           "Threes",          "Fours",
    "Fives",      "Sixes",          "Three of a Kind", "Four of a Kind",
    "Full House", "Small Straight", "Large Straight",  "Yahtzee!",
    "Chance"};

enum GameStates {
  PRE_GAME,        // before the first roll of the game
  MID_ROUND,       // when player is able to roll
  END_ROUND,       // when player is out of rolls
  BETWEEN_ROUNDS,  // after player picks a category
  END_GAME         // when all categories are scored
};

class Engine {
 public:
  Engine();
  void Setup();

  // Functions for sending info to the engine
  void RollDice();
  void UpdateKeepFlag(int index, bool keep);
  void AddCategoryValueToScore(int index);  // also applies bonuses

  // Functions for retrieving info from the engine
  GameStates GetGameState();
  int GetRollNumber();
  int GetScore();
  int GetUpperSectionScore();
  bool UpperSectionBonusEarned();
  std::array<int, kNumDice> GetDiceValues();
  std::array<int, kNumCategories> GetCategoryValues();

 private:
  struct Die {
    Die();
    void Roll();
    int value;
    bool keep;
  };

  // Functions for determining category values
  bool HasThreeOfAKind(std::array<int, kMaxDieValue> counts);
  bool HasFourOfAKind(std::array<int, kMaxDieValue> counts);
  bool HasFullHouse(std::array<int, kMaxDieValue> counts);
  bool HasSmallStraight(std::array<int, kMaxDieValue> counts);
  bool HasLargeStraight(std::array<int, kMaxDieValue> counts);
  bool HasYahtzee(std::array<int, kMaxDieValue> counts);

  // Helper functions
  void CalculateCategoryValues();
  std::array<int, kMaxDieValue> CountDiceTypes();  // counts # of each die value
  int CalculateLongestStraight(std::array<int, kMaxDieValue> counts);
  void HandleYahtzee(int dice_total);

  GameStates state_;
  int roll_number_;
  int round_number_;
  int score_;
  int upper_section_score_;
  bool upper_section_bonus_earned_;
  bool yahtzee_bonus_enabled_;
  bool yahtzee_category_filled_;  // for joker rules
  std::array<Die, kNumDice> dice_;
  std::array<int, kNumCategories> category_values_;
};

}  // namespace yahtzee
