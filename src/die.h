#include "ofMain.h"

namespace yahtzee {

class Die {
    public:
        Die();

        void Roll();
        void Draw(float x, float y, float w, float h);

        int get_value();

    private:
        int value_;
        ofImage image_;

        std::string GetImagePath(int value);
};

}