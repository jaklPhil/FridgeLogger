#pragma once
#include <Arduino.h>
#define CT_PIN 18

#define SUPPLY_VOLTAGE  3300 //in mV
#define ADC_BITS  12
#define ADC_COUNTS  (1<<ADC_BITS)

class  CtSensor{
    public:
    double ctCalcIrms(unsigned int Number_of_Samples);
    void setupCT();
};  
