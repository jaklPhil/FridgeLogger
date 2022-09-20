# FridgeLogger
 An ESP32 based measuring device for a houshold Fridge.
 The Purpous is to analysing the correlation between door openings and energy conmsumption.
#### Software concept
![alt text](readme/achrichtektur.png "Software concept")

#### Hardware concept
![alt text](readme/Hardware%20Setup.png "Hardware concept")


## Build

### Software (ESP32)
#### 1. Install [PlatformIO](https://platformio.org/platformio-ide) extension.
#### 2. Configure your Wifi [setupWifi.h](ESP32/src/espService/setupWifi.h).
#### 3. Connect your ESP32 an run PlatformIO "upload". 

### Software (ESP32)
#### 1. Install [PlatformIO](https://platformio.org/platformio-ide) extension.
#### 2. Configure your Wifi [setupWifi.h](src/espService/setupWifi.h).
#### 3. Connect your ESP32 an run PlatformIO "upload". 

### Hardware
#### Components
| Description         | Component   | amount  	   |
| ------------------- |-------------|-------------|
| Microcontroller     | ESP32       | 1           |
| temperature sensor  | DHT22       | 5           |
| Distance sensor     | HC-SR04     | 1           |
| Current transformer | ZMCT103C    | 1           |

#### Wiring diagramm
![alt text](readme/circuit.png "ESP Wirining")
