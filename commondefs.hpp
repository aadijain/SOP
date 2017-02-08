#ifndef COMMONDEFS_H
#define COMMONDEFS_H

#define PI 3.1415
#define TIMESTEP 20

struct Point {
    double r;
    double theta;
    bool breakpoint;
};
struct Line {
    double alpha;
    double p;
};
struct Circle {
    double radius;
    double x,y;
};

enum type { POINT, LINE, CIRCLE };

struct Feature {
    type ftype;
    union obj {
        Circle c;
        Point p;
        Line l;
    };
};
#endif
