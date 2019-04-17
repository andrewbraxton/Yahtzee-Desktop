#include "die.h"

using namespace yahtzee;

Die::Die() {
    Roll();
    Setup(image_.getWidth(), image_.getHeight());
    SetPosition(0, 0);
}

void Die::Setup(int w, int h) {
    width_ = w;
    height_ = h;
}

void Die::SetPosition(int x, int y) {
    x_ = x;
    y_ = y;
}

void Die::Roll() {
    int dice_roll = ofRandom(1,7);

    value_ = dice_roll;
    image_ = ofImage(GetImagePath(dice_roll));
}

void Die::Draw() {
    image_.draw(x_, y_, width_, height_);
}

int Die::get_value() {
    return value_;
}

std::string Die::GetImagePath(int value) {
    std::string path = "images/dice.png";
    path.insert(11, std::to_string(value));
    return path;
}