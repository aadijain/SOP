#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <math.h>
#include "commondefs.hpp"
#include "drawer.hpp"
#include "parser.hpp"

#define checkstep
// #define endpoints

using namespace std;

class Predictor {
    private:
        vector<Point> input_data;
        vector<MetaData> pred_data;
        vector<Feature> features;
        Parser pr;
        Drawer dr;
        Line getPredLine(int index);
        Line getPredRay(int index);
        Point getPredPoint(int index);
        double getPredThreshold(int index);

    public:
        static int NP;
        static int D0;
        static int RMAX;
        static int NORM;
        void draw();
        void update();
        void getRawData();
        void predict();
        // void extractFeatures();
        // void getStats();//print variance, covariance, falspositives, etc
        Predictor();
};

#endif
