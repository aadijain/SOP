#include "predictor.hpp"

int Predictor::NP;
int Predictor::D0;

void Predictor::getRawData()
{
    input_data = pr.getInputFromFile();
    pred_data.resize(input_data.size());
    features = pr.getSampleFeatures();
}
Predictor::Predictor() :dr()
{
    getRawData();
}
void Predictor::draw()
{
    Line l1 = getPredLine(dr.INDEX);
    Line l2 = getPredRay(dr.INDEX);
    Point p = getPredPoint(dr.INDEX);
    double th = predThreshold(dr.INDEX);

    dr = Drawer();
    dr.displayPoints(input_data);
    dr.displayMetaData(l1,l2,p,th);
    // dr.displayFeatures(features);
    dr.wait();
}
void Predictor::update()
{
    dr.displaySlider();
    dr.wait();
    NP = dr.NP;
    D0 = dr.D0;
    // printf("NP: %d\n",NP);
    // printf("D0: %d\n",D0);
}
double Predictor::predThreshold(int index)
{
    double r = sqrt(pow(input_data[index].x,2) + pow(input_data[index].y,2));
    double theta = atan2(input_data[index].y,input_data[index].x);
    double th = D0*(r/RMAX + (PI-theta)/PI)/NORM;
    return th;
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
	return l;
}
Line Predictor::getPredRay(int index)
{
    Line l;
    double theta = atan2(input_data[index].y,input_data[index].x);
    l.p = 0;
    l.alpha = PI/2 + theta;
    return l;
}
Point Predictor::getPredPoint(int index)
{
    if(index < NP)
        return input_data[index];
    Point p;
    Line l1 = getPredLine(index);
    Line l2 = getPredRay(index);
    double s = sin(l1.alpha - l2.alpha);
    p.x = (l2.p*sin(l1.alpha) - l1.p*sin(l2.alpha))/s;
    p.y = (l1.p*cos(l2.alpha) - l2.p*cos(l1.alpha))/s;
    p.breakpoint = false;
    return p;
}
// void Predictor::extractFeatures()
// {
//     for(int i = 0; i < input_data.size(); i++)
//     {
//         pred_data[i] = getPredPoint(i);
//     }
// }
