#include "predictor.hpp"

int main(int argc ,char *argv[])
{
    Predictor p;
    while(true)
    {
        // p.getRawData();
        p.update();
        p.draw();
    }
    return 0;
}
