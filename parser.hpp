#ifndef PARSER_H
#define PARSER_H
#include "commondefs.hpp"
#include <stdio.h>
#include <vector>

using namespace std;

class Parser
{
    public:
        vector<Point> getDataFromFile();
};
#endif
