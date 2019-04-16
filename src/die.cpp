#include "die.h"

#include <random>

using namespace yahtzee;

Die::Die() {
    Roll();
}

// code for random number generation taken from
// https://stackoverflow.com/a/7560564
void Die::Roll() {
    std::random_device rd; // obtain a random number from hardware
    std::mt19937 eng(rd()); // seed the generator
    std::uniform_int_distribution<> distr(1, 6); // define the range
    int dice_roll = distr(eng);

    value_ = dice_roll;
    image_ = ofImage(GetImagePath(dice_roll));
}

void Die::Draw(float x, float y, float w, float h) {
    image_.draw(x, y, w, h);
}

int Die::get_value() {
    return value_;
}

std::string Die::GetImagePath(int value) {
    std::string path = "images/dice.png";
    path.insert(11, std::to_string(value));
    return path;
}