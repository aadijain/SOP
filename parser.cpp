#include "parser.hpp"

vector<Point> Parser::getPolarInput()
{
    FILE *f = fopen("data.csv","r");
    vector<Point> v;
    Point p;
    double r ,theta;
    while(true)
    {
        fscanf(f,"%lf,%lf", &theta, &r);
        theta *= PI/180;
        p.x = r * cos(theta);
        p.y = r * sin(theta);
        if(feof(f))
            break;
        v.push_back(p);
    }
    fclose(f);
    return v;
}
vector<Point> Parser::getCartesianInput()
{
    FILE *f = fopen("data.csv","r");
    vector<Point> v;
    Point p;
    while(true)
    {
        fscanf(f,"%lf,%lf", &p.x, &p.y);
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
    Feature f1,f2,f3,f4,f5,f6,f7,f8;
    a.x = -50;          a.y = -50;
    b.x = 50;           b.y = 10;
    c.x = 55;           c.y = 50;
    d.x = 50;           d.y = 90;
    e.x = -30;          e.y = 150;
    c1.center = e;      c1.radius = 50;
    c2.center = b;      c2.radius = 20;
    l1.a = a;           l1.b = b;
    l2.a = b;           l2.b = d;
    f1.ftype = POINT;   f1.fobj.p = a;
    f2.ftype = POINT;   f2.fobj.p = b;
    f3.ftype = POINT;   f3.fobj.p = c;
    f4.ftype = POINT;   f4.fobj.p = d;
    f5.ftype = LINE;    f5.fobj.l = l1;
    f6.ftype = LINE;    f6.fobj.l = l2;
    f7.ftype = CIRCLE;  f7.fobj.c = c1;
    f8.ftype = CIRCLE;  f8.fobj.c = c2;
    v.push_back(f1);    v.push_back(f2);
    v.push_back(f3);    v.push_back(f4);
    v.push_back(f5);    v.push_back(f6);
    v.push_back(f7);    v.push_back(f8);
    return v;
}
