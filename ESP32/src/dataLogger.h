#pragma once
#include <Arduino.h>

//Task confuguration
#include "taskService/taskConfig.h"
//Sensors
#include "sensors/dhtSensor.h"
#include "sensors/powerSate.h"
#include "sensors/doorState.h"
//DataService
#include "dataService/dataSet.h"
#include "dataService/jsonEncoder.h"
#include "dataService/httpService.h"

class DataLogger : public DHTSensors, public DoorState, public PowerState, public JsonEncoder, public HttpService{
    private:
        //Singleton
        DataLogger();
        //Variables
        size_t set_num;
        DataSet dataSets[DATA_SET_NUM];		
        String jsonString;
        long setId,lastTime;
        //Functions
        long get_SetID();
        long get_SetTimeSpan();
        size_t get_SetNum();
        DataSet get_SetData();

    public:
        //Singleton
        DataLogger(const DataLogger&) = delete;
        static DataLogger& Get(){
            static DataLogger s_instance;
            return s_instance;
        }
        //Functions
        void push_LightToPowerSate();
        void collect_CurrentSet();
        void post_JsonData();
};





