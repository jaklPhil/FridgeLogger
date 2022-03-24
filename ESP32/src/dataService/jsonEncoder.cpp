#include <Arduino.h>
#include <ArduinoJson.h>
#include "dataService/jsonEncoder.h"



//create Json String from Saved data in FridgeModel
String JsonEncoder::createJSONstr(DataSet* dataSets) {
     String JSONstr;
    //doc size: https://arduinojson.org/v6/assistant/
    DynamicJsonDocument doc(8192);

    //Data object
    JsonObject data = doc.createNestedObject("data");
    data["numOfSets"] = DATA_SET_NUM;
    data["numOfDHT"] = NUM_OF_DHT;
    //Datasets Array
    JsonArray array_datasets = data.createNestedArray("datasets");
    for (size_t set_num = 0; set_num < DATA_SET_NUM; set_num++){

        //Datatset
        JsonObject dataset = array_datasets.createNestedObject();
        dataset["id"] = dataSets[set_num].id;
        dataset["timeSpan"] = dataSets[set_num].dataTimeSpan;

        //Door object
        JsonObject data_datasets_Door = dataset.createNestedObject("Door");
        data_datasets_Door["openAngle"] = dataSets[set_num].doorState.angle;
        data_datasets_Door["openState"] = dataSets[set_num].doorState.openState;
        data_datasets_Door["openTime"] = dataSets[set_num].doorState.openTime;

        //Power Sate
        JsonObject data_datasets_Power = dataset.createNestedObject("Power");
        data_datasets_Power["powerState"] = dataSets[set_num].powerState.powerMode;
        // data_datasets_Power["energyPeriod"] = dataSets[set_num].powerState.energyPeriod;
        data_datasets_Power["timeInState"] = dataSets[set_num].powerState.timeInState;
        data_datasets_Power["powerAvg"] = dataSets[set_num].powerState.powerAvg;

        //DHT Sensors
        JsonArray array_DHTSensors = dataset.createNestedArray("DHTSensors");
        for (size_t dhtNum = 0; dhtNum < NUM_OF_DHT; dhtNum++ ){
            JsonObject DHTSensor = array_DHTSensors.createNestedObject();
            DHTSensor["Tmp"] = dataSets[set_num].dhtSensors[dhtNum].temperatur;
            DHTSensor["Humid"] = dataSets[set_num].dhtSensors[dhtNum].humidity;
        }
    } 

    serializeJson(doc, JSONstr); 
    //Serial.println("JSONstr");
    return JSONstr; 
}

