#ifndef DRAWER_H
#define DRAWER_H

#include "commondefs.hpp"
#include <stdio.h>
#include <vector>
#include <opencv2/opencv.hpp>
// #include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
// #include <opencv2/imgcodecs.hpp>
#define WIN_SIZE_X 500
#define WIN_SIZE_Y 500

using namespace std;
// using namespace cv;
class Drawer
{
    private:
        cv::Mat image;
    public:
        static int NP,D0,INDEX;
        Drawer();
        void displayPoints(vector<Point> v);
        void displayFeatures(vector<Feature> v);
        void displayMetaData(Line l1, Line l2, Point p, double th);
        void displaySlider();
        void wait();
        static void ifMoved(int v,void* data);
};
#endif
