#include "predictor.hpp"

int Predictor::NP;
double Predictor::D0;
double Predictor::QTH;
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
    dr.displayFeatures(features);
    dr.wait();
}
void Predictor::update()
{
    dr.displaySlider();
    // dr.wait();
    NP = dr.NP;
    D0 = dr.D0/3.0;
    QTH = dr.QTH/2.0;
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

void Predictor::circleFit(int start, int end, Circle &c)
{
    double sum_x=0, sum_x2=0, sum_y=0, sum_y2=0, sum_z=0, sum_z2=0, sum_xy=0, sum_xz=0, sum_yz=0, n=0;
    n = end - start + 1;
    for(int i = start; i <= end; i++)
    {
        double tx,ty,tz;
        tx = input_data[i].x;
        ty = input_data[i].y;
        tz = tx*tx + ty*ty;
        sum_x  += tx;
        sum_x2 += tx * tx;
        sum_y  += ty;
        sum_y2 += ty * ty;
        sum_z  += tz;
        sum_z2 += tz * tz;
        sum_xy += tx * ty;
        sum_xz += tx * tz;
        sum_yz += ty * tz;
    }
    Eigen::Matrix3f A;
    Eigen::Vector3f b, x;
    A << sum_x2, sum_xy, sum_x, sum_xy, sum_y2, sum_y, sum_x, sum_y, n;
    b << sum_xz, sum_yz, sum_z;
    x = A.colPivHouseholderQr().solve(b);
    c.center.x = x(0)/2;
    c.center.y = x(1)/2;
    c.radius = sqrt(x(2) + x(0)*x(0)/4 + x(1)*x(1)/4);
}
double Predictor::lineFit(int start,int end, Line &l)
{
	double xbar=0,ybar=0,xdev=0,ydev=0,devprod=0,xdev2=0,ydev2=0,r2=0;
	for(int i = start; i <= end; i++)
	{
		xbar += input_data[i].x;
		ybar += input_data[i].y;
	}
	xbar = xbar/(end -start + 1);
	ybar = ybar/(end -start + 1);
	for(int i = start; i <= end; i++)
	{
		xdev = input_data[i].x - xbar;
		ydev = input_data[i].y - ybar;
		devprod += xdev * ydev;
		xdev2 += xdev * xdev;
		ydev2 += ydev * ydev;
	}
	l.alpha = 0.5 * atan2(-2*devprod, ydev2-xdev2);
	l.p = xbar*cos(l.alpha) + ybar*sin(l.alpha);

    double err = 0;
    for(int i = start; i <= end; i++)
	{
		double d = input_data[i].x * cos(l.alpha) + input_data[i].y * sin(l.alpha) - l.p;
        err += d*d;
	}
    return err/(end -start + 1);
    // r2  = devprod * devprod;
    // r2 /= xdev2 * ydev2;
    // return r2;
}

double Predictor::lineSegmentFit(int start, int end, LineSegment &l)
{
    Line lt;
    Point p1,p2;
    double q, d1,d2;
    q = lineFit(start,end,lt);
    p1 = input_data[start];
    p2 = input_data[end];
    d1 = p1.x * cos(lt.alpha) + p1.y * sin(lt.alpha) - lt.p;
    d2 = p2.x * cos(lt.alpha) + p2.y * sin(lt.alpha) - lt.p;
    p1.x -= d1 * cos(lt.alpha);
    p1.y -= d1 * sin(lt.alpha);
    p2.x -= d2 * cos(lt.alpha);
    p2.y -= d2 * sin(lt.alpha);
    l.a = p1;
    l.b = p2;
    return q;
}

Line Predictor::getPredLine(int index)
{
    Line l;
    lineFit(index-NP, index-1, l);
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
}

void Predictor::extractFeatures()
{
    int start=0,end=0;
    Circle c;
    LineSegment l;
    Feature f;
    for(int i = 1; i <= pred_data.size(); i++)
    {
        if(i == pred_data.size() || pred_data[i].breakpoint)
        {
            double q = lineSegmentFit(start,end,l);
            f.len = end - start + 1;
            if(f.len == 1)
            {
                f.fobj.p = input_data[start];
                f.ftype = POINT;
            }
            else if(q <= QTH)
            {
                f.fobj.l = l;
                f.ftype = LINE;
            }
            else
            {
                circleFit(start,end,c);
                f.fobj.c = c;
                f.ftype = CIRCLE;
            }
            features.push_back(f);
            start = end = i;
        }
        else
            end++;
    }
}
