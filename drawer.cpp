#include "drawer.hpp"

int Drawer::NP = 3;
int Drawer::D0 = 10;
int Drawer::INDEX = 0;

// void Drawer::ifMoved(int v,void* data)
// {
//     if(INDEX < NP)
//         INDEX = NP;
//     //Drawer *d = (Drawer*)data;
//     //printf("v: %d\n",v);
// }
Drawer::Drawer()
{
    cv::namedWindow("Window",1);
    image = cv::Mat::zeros(WIN_SIZE_X, WIN_SIZE_Y, CV_8UC3 );
}
void Drawer::displayMetaData(MetaData d)
{
    if(INDEX < NP) return;
    cv::Point p1,p2,p3,p4;
    p1.x = d.p.x - LEN * sin(d.l1.alpha) + XSHIFT;
    p1.y = d.p.y + LEN * cos(d.l1.alpha) + YSHIFT;
    p2.x = d.p.x + LEN * sin(d.l1.alpha) + XSHIFT;
    p2.y = d.p.y - LEN * cos(d.l1.alpha) + YSHIFT;
    p3.x = XSHIFT;
    p3.y = YSHIFT;
    double r = sqrt(d.p.x*d.p.x + d.p.y*d.p.y);
    p4.x = 2*LEN * d.p.x/r + XSHIFT;
    p4.y = 2*LEN * d.p.y/r + YSHIFT;
    cv::Scalar sc = cv::Scalar(100,100,255);
    cv::line(image, p1, p2, sc);
    cv::line(image, p3, p4, sc);
    cv::circle(image, cv::Point(d.p.x + XSHIFT, d.p.y + YSHIFT), d.th, sc);
    cv::circle(image, p3, 3, sc);
    cv::imshow("Window", image);
}
void Drawer::displayPoints(vector<Point> v, vector<MetaData> d)
{
    vector<Point>::iterator it = v.begin();
    vector<MetaData>::iterator jt = d.begin();
    while(it!=v.end())
    {
        if(jt->breakpoint)
            cv::circle(image, cv::Point(it->x + XSHIFT, it->y + YSHIFT),2,cv::Scalar(255,255,100));
        else
            cv::circle(image, cv::Point(it->x + XSHIFT, it->y + YSHIFT),2,cv::Scalar(100,100,255));
        it++;
        jt++;
    }
    cv::imshow("Window", image);
}
void Drawer::displayFeatures(vector<Feature> v)
{
    cv::Scalar sc = cv::Scalar(100,255,100);
    for(vector<Feature>::iterator it = v.begin(); it!=v.end(); it++)
    {
        switch(it->ftype)
        {
            case POINT:
                cv::circle(image, cv::Point(it->fobj.p.x + XSHIFT, it->fobj.p.y + YSHIFT),2,sc);
                break;
            case CIRCLE:
                cv::circle(image, cv::Point(it->fobj.c.center.x + XSHIFT, it->fobj.c.center.y + YSHIFT),it->fobj.c.radius,sc);
                break;
            case LINE:
                cv::line(image, cv::Point(it->fobj.l.a.x + XSHIFT, it->fobj.l.a.y + YSHIFT),cv::Point(it->fobj.l.b.x + XSHIFT, it->fobj.l.b.y + YSHIFT),sc);
                break;
        }
    }
    cv::imshow("Window", image);
}
void Drawer::displaySlider()
{
    // cv::createTrackbar( "NP:", "Window", &Drawer::NP, 10,Drawer::ifMoved,this);
    // cv::createTrackbar( "D0:", "Window", &Drawer::D0, 100,Drawer::ifMoved,this);
    cv::createTrackbar( "NP:", "Window", &Drawer::NP, 10);
    cv::createTrackbar( "D0:", "Window", &Drawer::D0, 100);
    cv::createTrackbar( "INDEX:", "Window", &Drawer::INDEX, 40);
}
void Drawer::wait()
{
    cv::waitKey(TIMESTEP);
}
