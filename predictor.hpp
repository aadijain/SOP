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
// #define NP 3
#define D0 50
#define RMAX 100
#define NORM 1

using namespace std;

class Predictor {
    private:
        vector<Point> input_data;
        vector<Point> pred_data;
        vector<Feature> features;
        Parser pr;
        Drawer dr;
        void getRawData();
        // Line getPredLine(int index);
        // Line getPredRay(int index);
        // Point getpredPoint(int index);
        // double predThreshold(int index);

    public:
        static int NP;
        void draw();
        void update();
        // void draw(int index);
        // void extractFeatures();
        // void getStats();//print variance, covariance, falspositives, etc
        Predictor();
};

#endif
