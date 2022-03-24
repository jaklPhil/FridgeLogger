#pragma once
#include <Arduino.h>

//***Data Deffinition
#define DATA_PER_SECOND 1

class HttpService{
    public:
    static void httpPost(String JSONstr);
};
