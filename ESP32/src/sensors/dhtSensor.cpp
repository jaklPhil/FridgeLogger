#include "dhtSensor.h"
//DHT definition
DHT dht[] = {
  {DHT1_PIN, DHTTYPE},
  {DHT2_PIN, DHTTYPE},
  {DHT3_PIN, DHTTYPE},
  {DHT4_PIN, DHTTYPE},
  {DHT5_PIN, DHTTYPE},
};

//Konstruktor
DHTSensors::DHTSensors(){
    for (int sensor_num = 0; sensor_num < NUM_OF_DHT; sensor_num++ ){
        dhtVal[sensor_num].humidity = 0;
        dhtVal[sensor_num].temperatur = 0;
        isReading[sensor_num] = false;
    }
}

DHTSensor* DHTSensors::return_DHTModels(){
        return dhtVal;
}

// loop dht array, initialise DHT sensors
void DHTSensors::setup_dhtSensors(){
    for (auto& sensor : dht) {
        sensor.begin();
    }
} 

void DHTSensors::readSensor(int sensor_num){
    float h = 0;
    float t = 0;
    //Read Sensor
    h = dht[sensor_num].readHumidity();
    t = dht[sensor_num].readTemperature();
     
    //filter nan readings
    dhtVal[sensor_num].humidity = isnan(h) ? 0 : h;
    dhtVal[sensor_num].temperatur = isnan(t) ? 0 : t;
}

//read all DHT sensors
void DHTSensors::read_DhtSensors(){
     for (int sensor_num = 0; sensor_num < NUM_OF_DHT; sensor_num++ ){
            readSensor(sensor_num);
    }
}
