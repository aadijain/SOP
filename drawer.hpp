#ifndef DRAWER_H
#define DRAWER_H

#include "commondefs.hpp"
#include <stdio.h>
#include <vector>
// #include <opencv2/opencv.hpp>
// #include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>
// using namespace cv;
using namespace std;
class Drawer
{
    private:
    public:
        static int NP,D0;
        void displayPoints(vector<Point> v);
        void displayFeatures(vector<Point> v);
        void displaySlider();
        void wait();
        static void ifMoved(int v,void* data);
};
#endif
