#include "predictor.hpp"

void Predictor::getRawData()
{
    Parser pr;
    input_data = pr.getDataFromFile();
}

Predictor::Predictor()
{
    getRawData();
}

void Predictor::draw()
{
    Drawer dr;
    dr.displayPoints(input_data);
    dr.displayFeatures(pred_data);
}
