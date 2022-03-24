#pragma once
#include <Arduino.h>
#include "state.h"
#include "ctSensor.h"

//AVG Array size
#define MAX_READINGS 50
//Compare Readings AVG basis
#define COMPARE_READINGS 10


#define STATE_0 0.0   //***State 0***   Light off, Pump off
#define STATE_1 15.0  //***State 1***   Light on,  Pump offf
#define STATE_2 58.0  //***State 2***   Light off, Pump on
#define STATE_3 65.0  //***State 3***   Light on,  Pump on


#define ampThreshold 0.15
#define startupTime 3 //in senconds

struct Power {
	size_t powerMode; 	//Fridge state
	long timeInState;	//Time state is active in ms
	float powerAvg;     //Average power per second


};

class PowerState : public State, public CtSensor{
    private:
        Power power;
        boolean pumpState, lightState;
        double ctReadings[MAX_READINGS];
        double getAvgCTReadings(int fromSample, int sampleNum);
        void calc_PumpState();
        size_t calc_PowerState();
        void set_CtReading(double reading);

    public:
        PowerState();
        void read_CtSensor();
        void set_LightState(boolean val);
        void update_PowerState();
        Power return_PowerState();
};
