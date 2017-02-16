#include "parser.hpp"

vector<Point> Parser::getInputFromFile()
{
    FILE *f = fopen("polar_data.in","r");
    vector<Point> v;
    Point p;
    double r ,theta;
    while(true)
    {
        fscanf(f,"%lf %lf", &theta, &r);
        theta *= PI/180;
        p.x = r * cos(theta);
        p.y = r * sin(theta);
        p.breakpoint = false;
        if(feof(f))
            break;
        v.push_back(p);
    }
    fclose(f);
    return v;
}
vector<Feature> Parser::getSampleFeatures()
{
    vector<Feature> v;
    Point a,b,c,d,e;
    Circle c1,c2;
    LineSegment l1,l2;
    Feature f1,f2,f3,f4,f5,f6,f7;
    a.x = 0;     a.y = 0;
    b.x = 10;    b.y = 10;
    c.x = 20;    c.y = 30;
    d.x = 50;    d.y = 50;
    e.x = -30;   e.y = -50;
    c1.center = c;    c1.radius = 10;
    c2.center = d;    c2.radius = 20;
    l1.a = a;   l1.b = b;
    l2.a = b;   l2.b = c;
    f3.ftype = LINE;    f3.fobj.l = l1;
    f5.ftype = LINE;    f5.fobj.l = l2;
    f4.ftype = CIRCLE;  f4.fobj.c = c1;
    f6.ftype = CIRCLE;  f6.fobj.c = c2;
    f1.ftype = POINT;   f1.fobj.p = a;
    f2.ftype = POINT;   f2.fobj.p = d;
    f7.ftype = POINT;   f7.fobj.p = e;
    v.push_back(f1);
    v.push_back(f2);
    v.push_back(f3);
    v.push_back(f4);
    v.push_back(f5);
    v.push_back(f6);
    v.push_back(f7);
    return v;
}
