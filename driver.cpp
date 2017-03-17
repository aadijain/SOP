#include "predictor.hpp"

int main(int argc ,char *argv[])
{
    while(true)
    {
        Predictor p;
        p.update();
        p.predict();
        p.extractFeatures();
        p.draw();
    }
    return 0;
}
