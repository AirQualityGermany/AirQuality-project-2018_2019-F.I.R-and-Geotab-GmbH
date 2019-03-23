# How to install this sketch to a LOLIN32 development board

1. Install the latest Arduino IDE: https://www.arduino.cc/
2. Install the ESP32 Arduino Core: https://github.com/espressif/arduino-esp32
3. Replace the BLEAdvertising.h file with the one from this repository
4. Install the following libraries:
  * Adafruit Sensor library: https://github.com/adafruit/Adafruit_Sensor
  * Adafruit BME280 library: https://github.com/adafruit/Adafruit_BME280_Library
  * The modified version of Felix Galindos HPMA115S0 library from this repository
5. Upload the code (ESP32_BME280_HPM_Beacon_v1.1.ino) to the LOLIN32 board


1. After you've installed the Arduino core and the ESP32 libraries, search for the file named "BLEAdvertising.h" on your computer:
image.png

The one you are looking for is the one located in the Arduino...\packages\esp32\... folder.

2. This is the file that needs to be replaced. So download the replacement file from the repository and save it to some temporary location. (Select "Raw" to be able to save the file with your browser)
3. Select the newly downloaded file and overwrite the file in the library 
4. You're done with that step. Now you can continue with the installation with the three other libraries. You'll find a great documentation about libary installation here: https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use
