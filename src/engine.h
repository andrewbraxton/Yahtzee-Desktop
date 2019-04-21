#pragma once

namespace yahtzee {

const int kNumCategories = 13;
const int kNumDice = 5;

class Engine {

    public:

    private:
        struct Die {
            Die();
            void Roll();
            int value_;
        };

};

}