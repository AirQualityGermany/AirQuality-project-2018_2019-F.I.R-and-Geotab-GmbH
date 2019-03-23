# Cooperation-F.i.R. (Center Smart Services) Geotab
Repository created to host any SW development activities around the Air Quality project between f.i.r and Geotab

# Github -Working with Directories
For this project files can be organized in directories. A new directory can be created using : 
- Click on New File
- Type a folder name, followed by "/" to go down into a subfolder.
- Type '..' and then "/" to jump upwards one directory.
- Use the backspace key to edit the parent directory's name. (https://github.com/KirstieJane/STEMMRoleModels/wiki/Creating-new-folders-in-GitHub-repository-via-the-browser)

# Building the sensor node
What you will need:

Processors
- 1 x [Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/) or
- 1 x [ESP32 module](https://wiki.wemos.cc/products:lolin32:lolin32_lite) or any kind of micro controller

Sensors
- 1 x [Honeywell HPMA115S0 particle sensor](http://www.farnell.com/datasheets/2313714.pdf)
- 1 x [Bosch BME280 environmental sensor](https://www.adafruit.com/product/2652)
- 1 x [SGX Sensortech MICS-2714 or -4514 or -6414 gas sensors](https://www.sgxsensortech.com/sensor-selector/)
  - [e-Bay](www.e-bay.com)
    - (search for MICS-6814 Carbon Monoxide Nitrogen Oxygen Compact Sensor CO/NO2/NH3 Gas Sensor or similar)
    - (pinout available for -4514 only)
  - [Banggood](www.banggood.com)
    - (search for "CJMCU-4541 MICS-4514 Carbon Monoxide Nitrogen Oxygen Sensor CO/NO2/H2/NH3/CH4" or similar)
  - [Cooking Hacks](https://www.cooking-hacks.com/no2-gas-sensor-7596)
  - Alternative companies offer a variety of individual boards (e.g. SEEED, LIBELIUM etc.) where it seems that any board related to detecting NO2 or similar gases is making use of the SGX Senortech sensors.

Other
- 1 x microSD card (at least 8 GB, RASPI only)
- 1 x Molex 51021-0800 pigtail ([for example](https://www.mouser.de/) to connect the PM sesnor)
- DuPont female-female jumper cables ([for example](https://www.amazon.de/Aukru-20cm-female-female-Steckbr%C3%BCcken-Drahtbr%C3%BCcken/dp/B00OL6JZ3C))
- USB-to-MicroUSB cable
- 5V power source
- Ethernet cable (RASPI only)
- Maker equipment like soldering iron, cable, shrinking cable, cable ties, hotglue, super glue, heating gun, double sided tape, magnets (e.g. from old HDD's), USB car adapter and cable (long) for **in-vehicle** power supply, step down (12-24V, 3-5V out) for **ex-vehicle** power supply, USB power bank (10000mAh) for mobile power supply

## First prototype sensor based on the Raspberry Pi for static PM and temp readings with output via console
1. Download the latest RASPBIAN STRETCH LITE image from https://www.raspberrypi.org/downloads/raspbian/
2. Write the image to the SD card by following the official guide at https://www.raspberrypi.org/documentation/installation/installing-images/README.md
3. Create an empty file named "ssh" (simple textfile) on the boot partition of the microSD card (to enable the SSH server)
4. Plug the microSD card in the Raspberry Pi, connect it via Ethernet to your local network, and power it up using the microUSB cable
5. After it's booted up, connect to the Pi via SSH (with an SSH client like [PuTTY](https://www.putty.org/)). To find out the Pi's IP address, please check the DHCP clients on your routers admin page. The default user/pass of the Pi is pi/raspberry.
  - Option: Assuming that you are not having an Ethernet connection but you would be able to connect the RASPI via HDMI and Keyboard/Mouse, you could set up the WIFI connection right away (using **sudo raspi-config**). Once the WIFI is up and running, use **ifconfig** to determine the IP address necessary to connect via the PUTTY terminal.
6. If you've successfully logged in, please finalize the configuration of your Pi with the [raspi-config](https://www.raspberrypi.org/documentation/configuration/raspi-config.md) tool: **sudo raspi-config**. It's important to:
  - change the user password
  - set a unique hostname (current naming convention would be AirQuality_Sensor_x with x=1 (Maker Aachen), 2 (Geotab DE), 3 (F.i.R Aachen), 4 (Geotab CA)
  - set up the WLAN network
  - set the correct time zone and WiFi country
  - configure the necessary interfaces (SSH is already enabled, I2C needs to be turned on, shell output on the Serial interface needs to be *disabled*, but the Serial interface should be kept enabled)
  - expand the file system
7. If you're done with the configuration, restart the Pi with **sudo reboot now**. Check if all the changes are correct, then shut down it with **sudo shutdown now**, and remove the power cable.

### Hooking up the sensors
#### BME280
1. Solder the headers to the sensor PCB as shown in https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/assembly
2. Use four DuPont jumper wires to connect the sensor to the Raspberry Pi via I2C. (See "Raspberry Pi wired with I2C" on https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/python-circuitpython-test#python-computer-wiring-5-5. Pinout examples for RASPI 3 Model B (when using a different development board, please check the board pinout when connecting to the sensor):
- *3V3* (PIN 1) to sensor *VIN*
- *GND* (PIN 9) to sensor *GND*
- *SCL* (GPIO 3, PIN 5) to sensor *SCK*
- *SDA* (GPIO 2, PIN 3) to sensor *SDI*

#### Honeywell HPMA115S0
1. To make the wiring more straightforward, create a Molex-DuPont connector cable for the sensor. (Please see the [Datasheet](http://www.farnell.com/datasheets/2313714.pdf) for reference.)
- remove 4 cables from your 8 pin Molex pigtail (from right to left: pin 1, 3, 4 and 5)
- cut the DuPont connector from one end of 4 DuPont jumper wires
- splice the 4 remaining wires (pin 2, 6, 7 and 8) of your Molex pigtail to the jumper wires
2. Plug the Molex side of your connector cable to the sensor, and connect it to the Raspberry Pi via the following table (Pinout examples for RASPI 3 Model B (when using a different development board, please check the board pinout when connecting to the sensor)):
- *5V* (PIN 4) to sensor *Pin 2*
- *RXD* (GPIO 15, PIN 10) to sensor *Pin 6*
- *TXD* (GPIO 14, PIN 8) to sensor *Pin 7*
- *GND* (PIN 4) to sensor *Pin 8*

### Testing the sensors using *sensortext.py*
1. Boot up your Pi again, log in via SSH, and update it with the following command: **sudo apt-get update && sudo apt-get upgrade**
2. Install the Adafruit Python GPIO library: https://github.com/adafruit/Adafruit_Python_GPIO (check link for installation instructions)
3. Install the Adafruit BME280 library: https://github.com/adafruit/Adafruit_Python_BME280 (you can now use **git clone** command to install this library.)
4. Install the PySerial library: **pip install pyserial**
5. Install the ThingType HPMA115S0 library: https://github.com/ThingType/HPMA115S0_Python_library (use **git clone**; [Detailed documentation](https://thingtype.com/blog/using-an-hpma115s0-air-particles-sensor-with-a-raspberry-pi/))
6. Create a file (via **touch**) named `__init__`.py in the Adafruit_Python_BME280 and the HPMA115S0_Python directories, to make the importable in python. 
  - **Attention (status Aug 26 2018)**: The directory name HPMA115S0_Python_library has to be changed manually to HPMA115S0_Python.
7. Download the *sensortest.py* script from this repository. Ensure that the test file is stored inside the same directory that holds the ADAFRUIT and HPMA libraries as well. 
- Depending on your command skills, use either **wget** to transfer the file or **git clone** to copy the complete directory onto the RASPI.
8. Run it, to check if everything works as expected: **python sensortest.py**. Use CTRL-C to exit the program.

If you see valid data received from both sensors: congratulations, you've build yourself a RASPI based sensor node!

## Mobile sensor based on ESP32 controller for PM, NO2-gas and temp readings, using a LE-BT connection to Geotab Go7 telematic device and the MyGeotab cloud environment

1. See separate Readme inside ESP32 folder
2. See this [article](https://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use) to learn more about downloading libraries on the ARDUINO

## Hooking up the sensors
### BME280
1. Solder the headers to the sensor PCB as shown in https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/assembly
2. Use four DuPont jumper wires to connect the sensor to the Raspberry Pi via I2C. (See "Raspberry Pi wired with I2C" on https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/python-circuitpython-test#python-computer-wiring-5-5. Pinout examples for RASPI 3 Model B (when using a different development board, please check the board pinout when connecting to the sensor):
- *3V3* to sensor *VIN*
- *GND* to sensor *GND*
- *SCL* to sensor *SCK*
- *SDA* to sensor *SDI*

### Honeywell HPMA115S0
1. To make the wiring more straightforward, create a Molex-DuPont connector cable for the sensor. (Please see the [Datasheet](http://www.farnell.com/datasheets/2313714.pdf) for reference.)
- remove 4 cables from your 8 pin Molex pigtail (from right to left: pin 1, 3, 4 and 5)
- cut the DuPont connector from one end of 4 DuPont jumper wires
- splice the 4 remaining wires (pin 2, 6, 7 and 8) of your Molex pigtail to the jumper wires
2. Plug the Molex side of your connector cable to the sensor, and connect it to the Raspberry Pi via the following table (Pinout examples for RASPI 3 Model B (when using a different development board, please check the board pinout when connecting to the sensor)):
- *5V* to sensor *Pin 2*
- *RXD* to sensor *Pin 6*
- *TXD* to sensor *Pin 7*
- *GND* to sensor *Pin 8*

## Testing the sensors using *xx*
to be added

# Case manufacturing
With the help of a 3D printer, enclosures for the prototype sensors have been designed and remain work in progress. The housing is expected to be mounted to various mobile devices. Various interfacing base plates should be designed to allow for simple connection of the sensor to bicycles, cars and other mobile vehicles.

## STL files (to be updated)
1. Interface plate [vehicle](https://www.tinkercad.com/things/4Xz4JrNgmcE/editv2?sharecode=PCdHlDFncot4dArcW4hcWTQBgAOv3JHcGKH7myIfJUY=)
2. Interface plate bicycle [steering tube 57.2mm](https://www.tinkercad.com/things/jzmpo4tGQez/editv2?sharecode=1q4hmiGckp7A3iOZSZWTwA4aEF93UhBmeYaSY_0_uzE=)
3. Interface plate bicycle [seat post. 27.3mm](https://www.tinkercad.com/things/e2KdwUPzHp4-air-quality-bottom-adaptor-bike-seat-post-273mm/editv2?sharecode=tH-ZwkKY2VoDqsauvy4q2hLqFmQomjW-M0TOkkHZojo=)
4. Base plate [RASPI 3 model B](https://www.tinkercad.com/things/1gGCnCky6An-spectacular-allis/edit?&sharecode=RH8EePABKeKxCpGJCp6Acry-V-7am-ZyMxsMLUgiqa0=)
5. Cover RASPI [3 model B](https://www.tinkercad.com/things/88hw1V2CLJA/editv2?sharecode=Jthvr0qztWBviDRTiyt8R4J0hbHZ-XgIrdv957fNIdI=)
6. Cover [BME and HONEYWELL sensor](https://www.tinkercad.com/things/6zZtiDeTbDL/editv2?sharecode=hv0o3lNThIFnXw16Q4WmttxLdtT7ksC8-y0OA-khdSg=)

# Collection of real time data using *airq_logger.py*
to be added

# Making the sensor mobile, i.e. power plug independent
to be added

