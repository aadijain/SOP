#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#define PI 3.1415
#define TIMESTEP 200

struct Point {
    double x,y;
};
struct Line {
    double p,alpha;
};
struct LineSegment {
    Point a,b;
};
struct Circle {
    Point center;
    double radius;
};
struct MetaData{
    Line l1,l2;
    Point p;
    double th;
    bool breakpoint;
};
enum type { POINT, LINE, CIRCLE };
union obj {
    Circle c;
    Point p;
    LineSegment l;
};
struct Feature {
    type ftype;
    obj fobj;
    int len;
};
#endif
