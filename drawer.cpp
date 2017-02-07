#include "drawer.hpp"

void Drawer::displayPoints(vector<Point> v)
{
    printf("---POINT INFO----\n");
    for(vector<Point>::iterator it = v.begin(); it!=v.end(); it++)
        printf("%lf\t%lf\n",it->r,it->theta);
}

void Drawer::displayFeatures(vector<Point> v)
{
    printf("---FEATURE INFO----\n");
}
