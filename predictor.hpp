#ifndef PREDICTOR_H
#define PREDICTOR_H

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <math.h>
#include <Eigen/Dense>

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
        double lineFit(int start, int end, Line &l);
        double lineSegmentFit(int start, int end, LineSegment &l);
        void circleFit(int start, int end, Circle &c);
        Line getPredLine(int index);
        Line getPredRay(int index);
        Point getPredPoint(int index);
        double getPredThreshold(int index);

    public:
        static int NP, RMAX, NORM;
        static double D0,QTH;
        void draw();
        void update();
        void getRawData();
        void predict();
        void extractFeatures();
        // void getStats();//print variance, covariance, falspositives, etc
        Predictor();
};

#endif
