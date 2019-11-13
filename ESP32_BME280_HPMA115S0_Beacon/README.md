# How to install this sketch to a LOLIN32 development board

1. Install the latest Arduino IDE: https://www.arduino.cc/
2. Install the ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
3. Replace the BLEAdvertising: Search for the file named "BLEAdvertising.h" on your computer. Next, please download the replacement file from this repository (see list on top) and save it to a temporary location (select "Raw" to be able to save the file with your browser). Replace the original file with the temporary file. 
4. Install the following libraries:
  * Adafruit Sensor library: https://github.com/adafruit/Adafruit_Sensor
  * Adafruit BME280 library: https://github.com/adafruit/Adafruit_BME280_Library
  * The modified version of Felix Galindos HPMA115S0 library (see list on top).
5. Upload the code (Geotab_AirQuality_Beacon_v1.2.ino) to the LOLIN32 board

You'll find a great documentation about library installation under: https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use
