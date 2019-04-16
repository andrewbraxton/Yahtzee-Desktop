#include "die.h"

using namespace yahtzee;

Die::Die() {
    Roll();
}

void Die::Roll() {
    int dice_roll = ofRandom(1,7);

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