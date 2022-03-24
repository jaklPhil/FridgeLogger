#include <Arduino.h>
#include <Wifi.h>
#include "setupWifi.h"

// Device sleep time (sec) to reduce Joule heat
uint64_t DEEP_SLEEP_TIME_SEC = 10;
void espDeepSleep() {
    esp_sleep_enable_timer_wakeup(DEEP_SLEEP_TIME_SEC * 1000 * 1000);  // set deep sleep time
    esp_deep_sleep_start();   // enter deep sleep
}

void setupWIFI(){
// WiFi connection controlling parameters
    int statusCheckCounter = 0;
    const int CHECK_NUM_MAX = 100;

//Start
    WiFi.begin(WIFI_SSID, WIFI_PW);
    Serial.print("WiFi connecting");

//Wait till connected
    while (WiFi.status() != WL_CONNECTED) {
        if(statusCheckCounter > CHECK_NUM_MAX) {
            WiFi.disconnect();
            Serial.println("Deepsleep Start");
            espDeepSleep();
        }
        Serial.print(WiFi.status());
        delay(500);
        statusCheckCounter++;
    }
//Connected
    Serial.println("\nconnected");
}

