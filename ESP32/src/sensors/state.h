#pragma once
#include <Arduino.h>

class State{
    private:
        //State time
        size_t lastState;
        long stateSartTime, timeInState, maxTimeInState;
        //AVG 
        double avgVal;
        size_t avgSampleNum;
        boolean stateSwitchedInSet;

	public:
        State(); 
        double toAVG(double value);
        void resetData();
        long getStateTime(size_t state);
};

