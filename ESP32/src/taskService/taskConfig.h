#pragma once
#include "dataLogger.h"

//Sample perioads
#define CT_SAMPLE_PRERIOD 250 
#define DISTANCE_SAMPLE_PRERIOD 50
#define DHT_SAMPLE_PRERIOD 6000 
//Task Priority
#define SENSOR_PRIORITY 10
#define CALCULATION_PRIORITY 8
#define DATASET_PRIORITY 12
#define HTTP_PRIORITY 6

void setup_task();