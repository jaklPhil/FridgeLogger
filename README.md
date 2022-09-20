# FridgeLogger
 An ESP32 based measuring device for a houshold Fridge.
 The Purpous is to analysing the correlation between door openings and energy conmsumption.
#### Software concept
![alt text](readme/achrichtektur.png "Software concept")

#### Hardware concept
![alt text](readme/Hardware%20Setup.png "Hardware concept")


## Build
### Software (Google Apps Script)
#### 1. Create a new Google Sheets document.
#### 2. [Add Google Apps Script to Project] (https://developers.google.com/apps-script/guides/sheets#connecting_to_google_forms)
#### 3. [paste the code in your script.gs](Google Apps Script/loggerBackend.js).

### Software (ESP32)
#### 1. Install [PlatformIO](https://platformio.org/platformio-ide) extension.
#### 2. Configure your Wifi [setupWifi.h](ESP32/src/espService/setupWifi.h).
#### 2. Configure your Google Script endpoint [HTTP endpoint](https://github.com/jaklPhil/FridgeLogger/blob/2461b9a289d12748e377009df085bbd735967b8e/ESP32/src/dataService/httpService.cpp#L6)).
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
