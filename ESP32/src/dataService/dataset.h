#pragma once
#include "sensors/powerSate.h"
#include "sensors/doorState.h"
#include "sensors/dhtSensor.h"

#define DATA_SET_NUM 10

struct DataSet{
	Door doorState;
	Power powerState;
	DHTSensor dhtSensors[NUM_OF_DHT];
	long id, dataTimeSpan;
};