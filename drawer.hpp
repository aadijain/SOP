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
#define XSHIFT 250
#define YSHIFT 250
#define LEN 100

using namespace std;
// using namespace cv;
class Drawer
{
    private:
        cv::Mat image;
    public:
        static int NP,D0,INDEX;
        Drawer();
        void displayPoints(vector<Point> v, vector<MetaData> d);
        void displayFeatures(vector<Feature> v);
        void displayMetaData(MetaData d);
        void displaySlider();
        void wait();
        static void ifMoved(int v,void* data);
};
#endif
