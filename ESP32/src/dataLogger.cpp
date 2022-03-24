#include <Arduino.h>
#include "dataLogger.h"

#include "taskService/taskService.h"

//Konstruktor
DataLogger::DataLogger(){ 
    setId = 0;
    lastTime = 0;
    set_num = 0;
    jsonString = " ";
}

//returns current set_num, creates next
long DataLogger::get_SetID(){
    long tmpReturn = setId;
    setId++;
    return tmpReturn;
}

//mesures time for Dataset
long DataLogger::get_SetTimeSpan(){
    long tmpReturn =  millis() - lastTime;
    lastTime = millis();
    return tmpReturn;
}

//returns current State to record, creates JSON str
size_t DataLogger::get_SetNum(){
    size_t return_set_num = set_num;
    set_num++;
    if (set_num == DATA_SET_NUM){
        set_num = 0;
    }  
    return return_set_num;
}
void DataLogger::push_LightToPowerSate(){
    //to perform on singelton Element
    set_LightState(update_LightState());
}
//create and current Dataset
DataSet DataLogger::get_SetData(){
    DataSet tmpDataSet;
    //Dataset general
    tmpDataSet.id = get_SetID();
    tmpDataSet.dataTimeSpan = get_SetTimeSpan();

    //Door
    tmpDataSet.doorState = return_DoorState();
    push_LightToPowerSate();
    //Power
    tmpDataSet.powerState = return_PowerState();

    //Temperatur
    DHTSensor* tmpDHT = return_DHTModels();
    for (size_t sensorNum = 0; sensorNum < NUM_OF_DHT; sensorNum++ ){
        tmpDataSet.dhtSensors[sensorNum] = tmpDHT[sensorNum];  
        //Serial.println(dhtVal[sensorNum].temperatur); 
    }
    return tmpDataSet;
}


//Globals
void DataLogger::collect_CurrentSet(){
    //Get current set number
    size_t set_num = get_SetNum();
    //save current set
    dataSets[set_num] = get_SetData();

    //trigger upload after the maximum  of local datasets are collected
    if (set_num + 1 == DATA_SET_NUM){
        
        //create Json string with fully written Datasets
        jsonString = createJSONstr(dataSets);
        //Notify post Task and trigger upload
        notifyPost();
    }  
    //Print LoggerSet
    Serial.print("Dataset ");
    Serial.print(set_num);
    Serial.println();
}

void DataLogger::post_JsonData(){
        httpPost(jsonString);
}   



