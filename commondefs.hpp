#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#define PI 3.1415
#define TIMESTEP 200

struct Point {
    double x,y;
    bool breakpoint;
};
struct Line {
    Point a,b;
};
struct Circle {
    Point center;
    double radius;
};

enum type { POINT, LINE, CIRCLE };
union obj {
    Circle c;
    Point p;
    Line l;
};
struct Feature {
    type ftype;
    obj fobj;
};
#endif
