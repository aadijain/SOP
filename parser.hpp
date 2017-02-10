#ifndef PARSER_H
#define PARSER_H
#include "commondefs.hpp"
#include <stdio.h>
#include <vector>
#include <math.h>
using namespace std;

class Parser
{
    public:
        vector<Point> getInputFromFile();
        vector<Feature> getSampleFeatures();
};
#endif
