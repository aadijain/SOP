#include "drawer.hpp"

int Drawer::NP = 3;
int Drawer::D0 = 50;

void Drawer::ifMoved(int v,void* data)
{
    Drawer *d = (Drawer*)data;
    d->NP = Drawer::NP;
    d->D0 = Drawer::D0;
    printf("v: %d\n",v);
}
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

void Drawer::displaySlider()
{
    cv::namedWindow("Window",1);
    cv::createTrackbar( "NP:", "Window", &Drawer::NP, 10,Drawer::ifMoved,this);
    cv::createTrackbar( "D0", "Window", &Drawer::D0, 100,Drawer::ifMoved,this);
}
void Drawer::wait()
{
    cv::waitKey(TIMESTEP);
}
