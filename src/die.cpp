#include "die.h"

using namespace yahtzee;

Die::Die() {
    Roll();
}

void Die::Roll() {
    int dice_roll = ofRandom(1,7);
    value_ = dice_roll;
}

int Die::get_value() {
    return value_;
}