#include "predictor.hpp"

int main(int argc ,char *argv[])
{
    Predictor p;
    while(true)
    {
        p.draw();
        p.update();
        cv::waitKey(100);
    }
    return 0;
}
