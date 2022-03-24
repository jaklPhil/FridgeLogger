#pragma once
#include <Arduino.h>
#include "DHT.h"

#define DHTTYPE DHT22 
//Sensors
#define NUM_OF_DHT 5
#define DHT1_PIN 32
#define DHT2_PIN 14
#define DHT3_PIN 25
#define DHT4_PIN 26
#define DHT5_PIN 27


struct DHTSensor{
	float temperatur;
	float humidity;
};

class DHTSensors{
    private:
        boolean isReading[NUM_OF_DHT];
        DHTSensor dhtVal[NUM_OF_DHT];
        void readSensor(int sensorNum);   

    public:
        DHTSensors();
        DHTSensor* return_DHTModels();
        void setup_dhtSensors();
        void read_DhtSensors();

};
