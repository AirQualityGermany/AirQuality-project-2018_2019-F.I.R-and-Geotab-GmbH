# How to install this sketch to a LOLIN32 development board

1. Install the latest Arduino IDE: https://www.arduino.cc/
2. Install the ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
3. Replace the BLEAdvertising.h file with the one from this repository:
Search for the file named "BLEAdvertising.h" on your computer:
The one you are looking for is the one located in the Arduino...\packages\esp32\... folder.
This is the file that needs to be replaced. So download the replacement file from the repository and save it to some temporary location. (Select "Raw" to be able to save the file with your browser)
Select the newly downloaded file and overwrite the file in the library 
You're done with that step.
4. Install the following libraries:
  * Adafruit Sensor library: https://github.com/adafruit/Adafruit_Sensor
  * Adafruit BME280 library: https://github.com/adafruit/Adafruit_BME280_Library
  * The modified version of Felix Galindos HPMA115S0 library from this repository: https://github.com/felixgalindo/HPMA115S0
5. Upload the code (Geotab_AirQuality_Beacon_v1.2.ino) to the LOLIN32 board

You'll find a great documentation about library installation under: https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use
