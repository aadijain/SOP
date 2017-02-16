#include "predictor.hpp"

int Predictor::NP;
int Predictor::D0;
int Predictor::RMAX = 50;
int Predictor::NORM = 1;

double dist(Point p1, Point p2 = {0,0})
{
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return sqrt(dx*dx + dy*dy);
}
void Predictor::getRawData()
{
    input_data = pr.getCartesianInput();
    // input_data = pr.getPolarInput();
    pred_data.resize(input_data.size());
    // features = pr.getSampleFeatures();
}
Predictor::Predictor() :dr()
{
    getRawData();
}
void Predictor::draw()
{
    dr= Drawer();
    dr.displayPoints(input_data,pred_data);
    dr.displayMetaData(pred_data[dr.INDEX]);
    // dr.displayFeatures(features);
    dr.wait();
}
void Predictor::update()
{
    dr.displaySlider();
    // dr.wait();
    NP = dr.NP;
    D0 = dr.D0;
    // printf("NP: %d\tD0: %d\n",NP,D0);
}
double Predictor::getPredThreshold(int index)
{
    double r = dist(input_data[index]);
    double theta = fabs(pred_data[index].l1.alpha - pred_data[index].l2.alpha);
    if(theta > PI) theta -= PI;
    double th = D0*(r/RMAX + (PI-theta)/PI)/NORM;
    return pred_data[index].th = th;
}
Line Predictor::getPredLine(int index)
{
	double xbar=0,ybar=0,xdev=0,ydev=0,devprod=0,xdev2=0,ydev2=0;
	Line l;
	for(int start = index-NP; start < index; start++)
	{
		xbar += input_data[start].x;
		ybar += input_data[start].y;
	}
	xbar = xbar/NP;
	ybar = ybar/NP;
	for(int start = index-NP; start < index; start++)
	{
		xdev = input_data[start].x - xbar;
		ydev = input_data[start].y - ybar;
		devprod = devprod + (xdev * ydev);
		xdev2 = xdev2 + (xdev * xdev);
		ydev2 = ydev2 + (ydev * ydev);
	}
	l.alpha = 0.5 * atan2(-2*devprod, ydev2-xdev2);
	l.p = xbar*cos(l.alpha) + ybar*sin(l.alpha);
	return pred_data[index].l1 = l;
}
Line Predictor::getPredRay(int index)
{
    Line l;
    double theta = atan2(input_data[index].y,input_data[index].x);
    l.p = 0;
    l.alpha = PI/2 + theta;
    return pred_data[index].l2 = l;
}
Point Predictor::getPredPoint(int index)
{
    Point p;
    Line l1 = pred_data[index].l1;
    Line l2 = pred_data[index].l2;
    double s = sin(l1.alpha - l2.alpha);
    p.x = (l2.p*sin(l1.alpha) - l1.p*sin(l2.alpha))/s;
    p.y = (l1.p*cos(l2.alpha) - l2.p*cos(l1.alpha))/s;
    return pred_data[index].p = p;
}
void Predictor::predict()
{
    for(int i = 0; i < NP; i++)
        pred_data[i].breakpoint = true;
    for(int i = NP; i < input_data.size(); i++)
    {
        getPredLine(i);
        getPredRay(i);
        getPredPoint(i);
        getPredThreshold(i);
        if(dist(input_data[i], pred_data[i].p) > pred_data[i].th)
            pred_data[i].breakpoint = true;
    }
    #ifdef checkstep
    int ctr = NP;
    for(int i = NP; i < pred_data.size(); i++)
    {
        if(ctr == NP && !pred_data[i].breakpoint)
        {
            for(int j = 1; j <= NP-1; j++)
            {
                pred_data[i-j].breakpoint = false;
                ctr--;
            }
        }
        if(pred_data[i].breakpoint)
            ctr++;
        if(pred_data[i-NP].breakpoint)
            ctr--;
    }
    #endif
    #ifdef endpoints
    for(int i = 1; i < pred_data.size(); i++)
    {
        if(pred_data[i].breakpoint)
            pred_data[i-1].breakpoint = true;
    }
    pred_data.back().breakpoint = true;
    #endif
}
