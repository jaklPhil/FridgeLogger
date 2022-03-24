#include "doorState.h"
#include "powerSate.h"


//Class functions
DoorState::DoorState(){
    door.angle = 0;
    door.openState = false;
    door.openTime = 0;
    distanceReading= 0;
}

void DoorState::read_Distance(){
     distanceReading = getPINGDistanceValue();
}

//Distance from target point to anngle
float DoorState::getAngle(int dist_mm){
    double virtualDist, readingDist ,angle, cosAngle;
    readingDist = (dist_mm/10);

    //filter if reading is out of range
    if (readingDist > MAXIMUM_READING){
        readingDist = MAXIMUM_READING;
    }
    long adjustedDist = readingDist - MOUNT_OFFSET;
    //*** Kosunussatz                       
    virtualDist = pow(MOUNT_OFFCENTER, 2) + pow(adjustedDist, 2) + (2 * MOUNT_OFFCENTER * adjustedDist * cos((MOUNT_ANGLE) * DEG_TO_RAD));
    //Virtual lenght
    virtualDist = sqrt(virtualDist);
    //Kosunussatz
    cosAngle = ( pow(virtualDist, 2) + pow(MOUNT_OFFCENTER, 2) - pow(adjustedDist ,2) )/(2 * virtualDist * MOUNT_OFFCENTER);
    //To degrees
    angle = acos(cosAngle)* RAD_TO_DEG;
    return angle;
}

void DoorState::update_DoorState(){
    //Update Door Angle with current reading
    double tmpAngle = getAngle(distanceReading);
    door.angle = toAVG(tmpAngle);

    //Check for Open 
    boolean doorOpen = (tmpAngle > OPEN_THRESHOLD);
    door.openState = doorOpen;
    door.openTime = getStateTime(doorOpen);
}

boolean DoorState::update_LightState(){
    //Update Door Angle with current reading
    double tmpAngle = getAngle(distanceReading);
    //Check and submit light staus to powerMode
    return (tmpAngle > LIGHT_THRESHOLD);
}

//return last written door Model
Door DoorState::return_DoorState(){
    update_DoorState();
    resetData();
    return door;
} 




