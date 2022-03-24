#include "ctSensor.h"

//Half ct suplly voltage 
double ICAL = 2.5;
//bit tollerance
double tollerance = 60;
//offset in Bits for 0A line
double offsetI = 0;

double filteredI, sqI, Irms, sumI;  
int sampleI;


void CtSensor::setupCT()
{
    pinMode(CT_PIN, INPUT);
}

double CtSensor::ctCalcIrms(unsigned int Number_of_Samples)
{
    for (unsigned int n = 0; n < Number_of_Samples; n++)
    {
        //Raw value
        sampleI = analogRead(CT_PIN);
        
        //Offset from Sensor
        offsetI =(offsetI + (sampleI-offsetI)/(100));
        
        //Filtered Sensor Value
        filteredI = sampleI - offsetI;

        //
        sqI = filteredI * filteredI;

        sumI += sqI;
    }
    //Convert to Mains Amps
    double I_RATIO = ICAL *((SUPPLY_VOLTAGE/1000.0) / (ADC_COUNTS));
    Irms = I_RATIO * sqrt(sumI / Number_of_Samples);

    //Reset 
    sumI = 0;
    return Irms;
}




