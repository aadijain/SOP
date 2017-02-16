#include "predictor.hpp"

int main(int argc ,char *argv[])
{
    while(true)
    {
        Predictor p;
        p.update();
        p.predict();
        p.draw();
    }
    return 0;
}
