#include "parser.hpp"

vector<Point> Parser::getDataFromFile()
{
    FILE *f = fopen("polar_data.in","r");
    vector<Point> v;
    while(true)
    {
        Point p;
        p.breakpoint = false;
        fscanf(f,"%lf %lf", &p.r,&p.theta);
        if(feof(f))
            break;
        v.push_back(p);
    }
    return v;
}
