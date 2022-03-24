#include <Arduino.h>
#include "taskConfig.h"
//ESP
#include "espService/setupWifi.h"
//Sensors
#include "sensors/dhtSensor.h"
#include "sensors/ctSensor.h"

void setup_task(){
  Serial.begin(115200);
  // setup WIFI connection, wait until succeed connecting
  setupWIFI();

  //Setup sensors
  DataLogger::Get().setupCT();
  DataLogger::Get().setup_dhtSensors();
}



