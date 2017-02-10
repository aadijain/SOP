#include "drawer.hpp"

int Drawer::NP = 3;
int Drawer::D0 = 50;

// void Drawer::ifMoved(int v,void* data)
// {
//     Drawer *d = (Drawer*)data;
//     d->NP = Drawer::NP;
//     d->D0 = Drawer::D0;
//     printf("v: %d\n",v);
// }

Drawer::Drawer()
{
    cv::namedWindow("Window",1);
    image = cv::Mat::zeros(WIN_SIZE_X, WIN_SIZE_Y, CV_8UC3 );

}

void Drawer::displayPoints(vector<Point> v)
{
    for(vector<Point>::iterator it = v.begin(); it!=v.end(); it++)
        cv::circle(image, cv::Point(it->x + WIN_SIZE_X/2, it->y + WIN_SIZE_Y/2),2,cv::Scalar(100,100,100));
    cv::imshow("Window", image);
}

void Drawer::displayFeatures(vector<Feature> v)
{
    for(vector<Feature>::iterator it = v.begin(); it!=v.end(); it++)
    {
        switch(it->ftype)
        {
            case POINT:
                cv::circle(image, cv::Point(it->fobj.p.x + WIN_SIZE_X/2, it->fobj.p.y + WIN_SIZE_Y/2),2,cv::Scalar(100,255,100));
                break;
            case CIRCLE:
                cv::circle(image, cv::Point(it->fobj.c.center.x + WIN_SIZE_X/2, it->fobj.c.center.y + WIN_SIZE_Y/2),it->fobj.c.radius,cv::Scalar(100,100,255));
                break;
            case LINE:
                cv::line(image, cv::Point(it->fobj.l.a.x + WIN_SIZE_X/2, it->fobj.l.a.y + WIN_SIZE_Y/2),cv::Point(it->fobj.l.b.x + WIN_SIZE_X/2, it->fobj.l.b.y + WIN_SIZE_Y/2),cv::Scalar(255,100,100));
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
}
void Drawer::wait()
{
    cv::waitKey(TIMESTEP);
}
