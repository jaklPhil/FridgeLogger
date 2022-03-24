#include <Arduino.h>
#include "powerSate.h"

//*Class Functions
PowerState::PowerState(){
    pumpState = false;
    lightState = false;
}

//Calculate Average Value in Array of the Last recorded values 
double PowerState::getAvgCTReadings(int fromSample, int sampleNum){
    double tmpAVG = 0;
    for (size_t sample = fromSample; sample < sampleNum; sample++)
    {
        tmpAVG += ctReadings[sample];
    }
    //create AVG
    tmpAVG = tmpAVG/sampleNum;
    return tmpAVG;
}

//Set Fridge pump state after readings and update model
void PowerState::calc_PumpState(){ 
    //compare recent avg with pervius long time SVG, array is cut at Compare Readings
    double compare =  getAvgCTReadings(0, COMPARE_READINGS) - getAvgCTReadings( COMPARE_READINGS + 1, MAX_READINGS - (COMPARE_READINGS+1) );
    //Detect pump state
    if(pumpState){
        //if on: detect falling Amps 
        pumpState = (compare < - ampThreshold) ? false :  pumpState;
    } else {
        // if off: detect raising Amps 
        pumpState = (compare > ampThreshold) ? true :  pumpState;
    }
}

//calculate Power state of pump and light
size_t PowerState::calc_PowerState(){
    //Update pump and light state with current readings
    calc_PumpState();
    //Select power state
    if (lightState){
        return pumpState ? 3 : 1;
    } else{
        return pumpState ? 2 : 0;
    }
} 

//Global functions
void PowerState::update_PowerState(){
    float powerStates[] {STATE_0, STATE_1, STATE_2, STATE_3}; 
    //***Power Mode
    size_t currentMode = calc_PowerState();

    power.powerMode =  currentMode;
    //***Power Value
    power.powerAvg = powerStates[currentMode];
    //***State time
    power.timeInState = getStateTime(currentMode);
}

Power PowerState::return_PowerState(){
    update_PowerState();
    resetData();
    return power;
}

//set Light state, claculate new Power status
void PowerState::set_LightState(boolean lightState){
    this->lightState = lightState;
    //calculate and push new PowerState
    update_PowerState();
}

void PowerState::read_CtSensor(){
    double reading = ctCalcIrms(2500);
    set_CtReading(reading);
}

// save CT values in Array and Calculate Power State Values
void PowerState::set_CtReading(double reading){
    double newReading, tmpReading;

    //Push Reading to First 
    tmpReading = ctReadings[0];
    ctReadings[0] = reading;

     //move trough array, 
    for (size_t reading_num = 1; reading_num < MAX_READINGS; reading_num++)
    {
        //Variablentausch..    
        newReading= tmpReading;
        tmpReading = ctReadings[reading_num];
        ctReadings[reading_num] = newReading;
    }
    //calculate and push new PowerState
    update_PowerState();
}

