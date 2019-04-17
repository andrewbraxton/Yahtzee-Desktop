#include "ofMain.h"

namespace yahtzee {

class Die {
    public:
        Die();

        void Setup(int w, int h);
        void SetPosition(int x, int y);
        void Roll();
        void Draw();

        int get_value();

    private:
        int value_;

        ofImage image_;
        int x_;
        int y_;
        int width_;
        int height_;

        std::string GetImagePath(int value);
};

}