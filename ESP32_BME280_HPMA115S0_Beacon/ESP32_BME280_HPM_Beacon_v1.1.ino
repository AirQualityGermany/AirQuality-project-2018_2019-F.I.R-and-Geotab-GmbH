/***************************************************************************
  Geotab Airquality BLE Beacon - ESP32 edition v1.1
  Measured values: Temperature, Humidity, Barometric pressure, PM 2.5, PM 10
    
  Sources:
  - ESP32 libraries: https://github.com/espressif/arduino-esp32
  - Adafruit Sensor library: https://github.com/adafruit/Adafruit_Sensor
  - Adafruit BME280 library: https://github.com/adafruit/Adafruit_BME280_Library
  - Felix Galindos HPMA115S0 library: https://github.com/felixgalindo/HPMA115S0

  29.12.2018 - Tamás Halbrucker
 ***************************************************************************/

// Libraries to be included
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <HPMA115S0.h>
#include "esp_sleep.h"

// Defining the second hardware serial port on the LOLIN32 board for the HPMA115S0 sensor
HardwareSerial MySerial(1);
HPMA115S0 hpma115S0(MySerial);
// BME280 sensor via I2C
Adafruit_BME280 bme;
// Onboard LED
unsigned int LED = 2;

void setup() {
  pinMode(LED, OUTPUT);
  // Debug serial output
  Serial.begin(115200);
  Serial.println("Starting Geotab AirQBee Beacon");

  // Serial port defined to GPIO 16 and 17
  MySerial.begin(9600, SERIAL_8N1, 16, 17);

  // Initializing the BME280 sensor
  bool status;
  status = bme.begin(0x76);  
  if (!status) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      while (1);
  }
  else {
    Serial.println("BME280 found at adress 0x76");
    }

  // Initializing the HPMA115S0 sensor
  hpma115S0.Init();
  hpma115S0.StartParticleMeasurement();     
    
  digitalWrite(LED, HIGH);

  // Initializing the BLE server
  BLEDevice::init("Geotab AirQBee");
 
  BLEServer *pServer = BLEDevice::createServer();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  BLEAdvertisementData advertisementData;

  // Setting the necessary flags
  advertisementData.setFlags(ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT);

  // Reading temperature
  float tempfval = (float)bme.readTemperature();
  Serial.print("Temperature: ");
  Serial.println(tempfval);
  byte* temparray = (byte*) &tempfval;

  // Reading humidity
  float humifval = (float)bme.readHumidity();
  Serial.print("Humidity: ");
  Serial.println(humifval);
  byte* humiarray = (byte*) &humifval;

  // Reading barometric pressure
  float pressfval = (float)bme.readPressure();
  Serial.print("Barometric pressure: ");
  Serial.println(pressfval);
  byte* pressarray = (byte*) &pressfval;

  // Reading PM 2.5 and PM 10
  unsigned int pm2_5;
  unsigned int pm10;
  if (hpma115S0.ReadParticleMeasurement(&pm2_5, &pm10)) {
    Serial.println("PM 2.5: " + String(pm2_5) + " ug/m3" );
    Serial.println("PM 10: " + String(pm10) + " ug/m3" );
  }

  // Building the payload
  char manfdata[21];
  // Geotab company ID
  manfdata[0]= 0x75;
  manfdata[1]= 0x02;
  // Advertising packet version number
  manfdata[2]= 0x00;
  // TX Power Level
  manfdata[3]= 0xC6;
  // Battery level
  manfdata[4]= 0x64;
  // Temperature
  manfdata[5]= 0x07;
  manfdata[6]= temparray[1];
  manfdata[7]= temparray[2];
  manfdata[8]= temparray[3];
  // Relative humidity
  manfdata[9]= 0x09;
  manfdata[10]= humiarray[1];
  manfdata[11]= humiarray[2];
  manfdata[12]= humiarray[3];
  // Barometric pressure
  manfdata[13]= 0x0A;
  manfdata[14]= pressarray[1];
  manfdata[15]= pressarray[2];
  manfdata[16]= pressarray[3];
  // PM 2.5
  manfdata[17]= 0xE6;
  manfdata[18]= pm2_5;
  // PM 10
  manfdata[19]= 0xE7;
  manfdata[20]= pm10;

  for (int i = 0; i < 21; ++i) {
   Serial.print(manfdata [i], HEX);
   Serial.print(" ");
  }

  // Setting the payload for the advertisement data
  advertisementData.setManufacturerData(std::string(manfdata, 21));
  pAdvertising->setAdvertisementData(advertisementData);
  digitalWrite(LED, LOW);

  // Starting the advertisement
  pAdvertising->start();
  delay(100);
  // Stopping the advertisement
  pAdvertising->stop();
  // Deep sleep until the next cycle
  Serial.println("Entering deep sleep...");
  esp_deep_sleep(900000LL);
}

void loop() {
}