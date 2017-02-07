#ifndef DRAWER_H
#define DRAWER_H

#include "commondefs.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

class Drawer
{
    public:
        void displayPoints(vector<Point> v);
        void displayFeatures(vector<Point> v);
};
#endif
