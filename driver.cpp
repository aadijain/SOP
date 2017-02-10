#include "predictor.hpp"

int main(int argc ,char *argv[])
{
    Predictor p;
    while(true)
    {
        // p.getRawData();
        p.draw();
        p.update();
    }
    return 0;
}
