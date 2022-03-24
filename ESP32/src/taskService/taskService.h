#pragma once
#include "taskConfig.h"
#include "dataService/httpService.h"

#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
#define CONFIG_FREERTOS_CHECK_STACKOVERFLOW_PTRVAL


void notifyPost();
void runTaskService();
//Tasks
void postData(void *parameter);
void collectDataSet(void *parameter);
void calcPowerStatus(void *parameter);
void calcDoorStatus(void *parameter);
void read_DHT(void *parameter);
void read_CT(void *parameter);
void read_Distance(void *parameter);
void idle_test(void *parameter);