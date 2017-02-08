#include "predictor.hpp"

int Predictor::NP = 3;

void Predictor::getRawData()
{
    input_data = pr.getDataFromFile();
}
Predictor::Predictor()
{
    getRawData();
}

void Predictor::draw()
{
    //dr.displayPoints(input_data);
    //dr.displayFeatures(pred_data);
    dr.displaySlider();
    dr.wait();
}
void Predictor::update()
{
    NP = dr.NP;
    printf("NP: %d\n",NP);
}
