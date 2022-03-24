#include "state.h"

State::State(){
    //State time
    lastState = 0;
    timeInState = 0;
    stateSwitchedInSet = false;
    //AVG 
    avgVal= 0;
    avgSampleNum = 0;
}

double State::toAVG(double value){
    avgSampleNum++;
    avgVal += value;
    return avgVal/avgSampleNum;
}

void State::resetData(){
    avgSampleNum = 0;
    avgVal = 0;
    stateSwitchedInSet = false;
}

//calculate time in State, returns current or maximum time per Datatset
long State::getStateTime(size_t currentState){
    //Check for state Switch
    if (currentState !=  lastState){   
        //switch State - Reset Open Time
        stateSartTime = millis();
        //Save first switch in period for Dataset
        if(!stateSwitchedInSet){
            stateSwitchedInSet = true;
            maxTimeInState = timeInState;
        }
    }
    //set Last sate
    lastState  = currentState;
    //calcute State Time
    timeInState =  millis() - stateSartTime;
    //Return current time in State, if state switched maximum time in State
    long returnTime;
    if(stateSwitchedInSet && timeInState <= maxTimeInState){
        returnTime = maxTimeInState;
        // stateSwitchedInSet = false;
    } else{
        returnTime = timeInState;
    }
    //time in ms
    return returnTime;
}

