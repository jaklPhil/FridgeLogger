#pragma once
#include <Arduino.h>
#include "state.h"
#include "distanceSensor.h"
#define OPEN_THRESHOLD 1 //in deg
#define LIGHT_THRESHOLD 9 //in deg
#define MOUNT_ANGLE 80 //in deg
#define MOUNT_OFFCENTER 25 //in cm from angle
#define MOUNT_OFFSET 11.6 //minimal reading in cm
#define MAXIMUM_READING 60 //maximum reading in cm

struct Door{
	float angle;
	boolean openState;
	long openTime;
};

class DoorState : public State, public DistanceSensor{
    private:
        Door door;
        long distanceReading;
        float getAngle(int dist_mm);
        
    public:
        DoorState();
        void set_Distance(long dist) {distanceReading = dist;};
        void read_Distance(); 
        void update_DoorState();
        boolean update_LightState();
        Door return_DoorState();
};



