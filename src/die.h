#include "ofMain.h"

namespace yahtzee {

class Die {
    public:
        Die();

        void Roll();
        int get_value();
        
    private:
        int value_;
};

}