#include "predictor.hpp"

int Predictor::NP;
int Predictor::D0;

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
    D0 = dr.D0;
    printf("NP: %d\n",NP);
    printf("D0: %d\n",D0);
}
