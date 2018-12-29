# How to install this sketch to a LOLIN32 development board

1. Install the latest Arduino IDE: https://www.arduino.cc/
2. Install the ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
3. Overwrite the BLEAdvertising.h file with the one from this repository
4. Install the following libraries:
  * Adafruit Sensor library: https://github.com/adafruit/Adafruit_Sensor
  * Adafruit BME280 library: https://github.com/adafruit/Adafruit_BME280_Library
  * The modified version of Felix Galindos HPMA115S0 library from this repository:
5. Upload the code (ESP32_BME280_HPM_Beacon_v1.1.ino) to the LOLIN32 board
