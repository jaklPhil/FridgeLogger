#include "taskService.h"

//Notification handle
static TaskHandle_t xPostData = NULL;
static TaskHandle_t xCalc_Door, xCalc_Power = NULL;

void runTaskService(){
    //Setup
    setup_task();
    Serial.println("Start Tasks");

    //Update States
    xTaskCreatePinnedToCore( calcPowerStatus, "update Power Satus", 4096, NULL, CALCULATION_PRIORITY, &xCalc_Power, app_cpu); 
    xTaskCreatePinnedToCore( calcDoorStatus, "update Door Status", 2024, NULL, CALCULATION_PRIORITY, &xCalc_Door, app_cpu); 

    //Read Sensors
    xTaskCreatePinnedToCore( read_Distance, "read Distance", 2024, NULL, SENSOR_PRIORITY, NULL, app_cpu); 
    xTaskCreatePinnedToCore( read_DHT, "Read DHT", 6024, NULL, SENSOR_PRIORITY, NULL, app_cpu); 
    xTaskCreatePinnedToCore( read_CT, "Read CT", 2024, NULL, SENSOR_PRIORITY, NULL, app_cpu); 

    //Collect Dataset
    xTaskCreatePinnedToCore( collectDataSet, "collectData", 16200, NULL, DATASET_PRIORITY, NULL, app_cpu); 

    //Upload Data
    xTaskCreatePinnedToCore( postData, "PostData", 10024, NULL, HTTP_PRIORITY, &xPostData, app_cpu); 

    //Start Scheduler
    vTaskDelete(NULL);
    vTaskStartScheduler();
}

//Post notification
void notifyPost(){
        xTaskNotifyGive( xPostData );
}

void postData(void *parameter){
    while(1){
        //wait for notification
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        // notification recived,trigger upload json data
        DataLogger::Get().post_JsonData();
    }
}

//collect DataStes periodicly
void collectDataSet(void *parameter){
    while(1){
        TickType_t xLastCollectTime;
        xLastCollectTime = xTaskGetTickCount();
        //Collect set
        DataLogger::Get().collect_CurrentSet();
        vTaskDelayUntil(&xLastCollectTime ,1000 / portTICK_PERIOD_MS);
    }
}

//Calc states
void calcDoorStatus(void *parameter){ 
    while(1){
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
        //Calculate new Door state
        DataLogger::Get().update_DoorState(); 
        //Notify Power state for new Light state
        DataLogger::Get().push_LightToPowerSate();
        xTaskNotifyGive( xCalc_Power );
    }
}

void calcPowerStatus(void *parameter){ 
    while(1){
      //wait for ct or light reading
        ulTaskNotifyTake( pdTRUE, portMAX_DELAY );
      //Calculate new power state
        DataLogger::Get().update_PowerState();
    }
}

//Read Sensors
void read_CT(void *parameter){
    while(1){
        //Read Sensor and trigger power state calculation
         DataLogger::Get().read_CtSensor();
        //Notify Power state
        xTaskNotifyGive( xCalc_Power );
        vTaskDelay(CT_SAMPLE_PRERIOD/ portTICK_PERIOD_MS); 
    }
}
void read_Distance(void *parameter){
    while(1){
        // read distance and trigger door state calculation
        DataLogger::Get().read_Distance();
        //Notify Door state
        xTaskNotifyGive( xCalc_Door );
        vTaskDelay(DISTANCE_SAMPLE_PRERIOD/ portTICK_PERIOD_MS);
    }
}
void read_DHT(void *parameter){
    while(1){
       TickType_t xLastWakeTime;
        xLastWakeTime = xTaskGetTickCount();
        DataLogger::Get().read_DhtSensors();
        vTaskDelayUntil(&xLastWakeTime ,DHT_SAMPLE_PRERIOD/ portTICK_PERIOD_MS);
    }
}