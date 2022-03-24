#pragma once
#include <Arduino.h>

#define PING_DIST_PIN 2

class DistanceSensor{
    public:
    long getPINGDistanceValue();
};
