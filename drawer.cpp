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

double Ycoord(Line l, double x){
    return (l.p - x*cos(l.alpha))/sin(l.alpha);
}

void Drawer::displayMetaData(Line l1, Line l2, Point p, double th)
{
    if(INDEX < NP) return;
    Point p1,p2,p3,p4;
    p1.x = p.x - WIN_SIZE_X;    p1.y = Ycoord(l1,p1.x);
    p2.x = p.x + WIN_SIZE_X;    p2.y = Ycoord(l1,p2.x);
    p3.x = 0;                   p3.y = Ycoord(l2,p3.x);
    p4.x = 10 * p.x;           p4.y = Ycoord(l2,p4.x);
    cv::Scalar sc = cv::Scalar(100,100,255);
    cv::line(image, cv::Point(p1.x + WIN_SIZE_X/2, p1.y + WIN_SIZE_Y/2), cv::Point(p2.x + WIN_SIZE_X/2, p2.y + WIN_SIZE_Y/2), sc);
    cv::line(image, cv::Point(p3.x + WIN_SIZE_X/2, p3.y + WIN_SIZE_Y/2), cv::Point(p4.x + WIN_SIZE_X/2, p4.y + WIN_SIZE_Y/2), sc);
    cv::circle(image, cv::Point(p.x + WIN_SIZE_X/2, p.y + WIN_SIZE_Y/2), th, sc);
    cv::circle(image, cv::Point(WIN_SIZE_X/2,WIN_SIZE_Y/2), 3, sc);
    cv::imshow("Window", image);
}

void Drawer::displayPoints(vector<Point> v)
{
    for(vector<Point>::iterator it = v.begin(); it!=v.end(); it++)
        cv::circle(image, cv::Point(it->x + WIN_SIZE_X/2, it->y + WIN_SIZE_Y/2),2,cv::Scalar(255,100,100));
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
                cv::circle(image, cv::Point(it->fobj.p.x + WIN_SIZE_X/2, it->fobj.p.y + WIN_SIZE_Y/2),2,sc);
                break;
            case CIRCLE:
                cv::circle(image, cv::Point(it->fobj.c.center.x + WIN_SIZE_X/2, it->fobj.c.center.y + WIN_SIZE_Y/2),it->fobj.c.radius,sc);
                break;
            case LINE:
                cv::line(image, cv::Point(it->fobj.l.a.x + WIN_SIZE_X/2, it->fobj.l.a.y + WIN_SIZE_Y/2),cv::Point(it->fobj.l.b.x + WIN_SIZE_X/2, it->fobj.l.b.y + WIN_SIZE_Y/2),sc);
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
    cv::createTrackbar( "INDEX:", "Window", &Drawer::INDEX, 20);
}
void Drawer::wait()
{
    cv::waitKey(TIMESTEP);
}
