#include "drawer.hpp"

int n_slider;
// const int n_max=10;

void Drawer::ifMoved(int v,void* data)
{
    Drawer *d = (Drawer*)data;
    d->NP = v;
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
    cv::createTrackbar( "n Slider", "Window", &n_slider, 10,Drawer::ifMoved,this);
}
void Drawer::wait()
{
    cv::waitKey(TIMESTEP);
}
