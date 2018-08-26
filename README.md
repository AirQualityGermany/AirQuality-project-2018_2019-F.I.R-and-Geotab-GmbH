# Cooperation-RWTH-and-Geotab
Repository created to host any SW development activities around the Air Quality project between f.i.r and Geotab

# Building the sensor node (Prototypes #1-#4)
What you will need:
- 1 x [Raspberry Pi 3 Model B](https://www.raspberrypi.org/products/raspberry-pi-3-model-b/)
- 1 x [Honeywell HPMA115S0 particle sensor](http://www.farnell.com/datasheets/2313714.pdf)
- 1 x [Bosch BME280 environmental sensor](https://www.adafruit.com/product/2652)
- 1 x microSD card (at least 8 GB)
- 1 x Molex 51021-0800 pigtail ([for example](https://www.mouser.de/))
- DuPont female-female jumper cables ([for example](https://www.amazon.de/Aukru-20cm-female-female-Steckbr%C3%BCcken-Drahtbr%C3%BCcken/dp/B00OL6JZ3C))
- USB-to-MicroUSB cable
- 5V power source
- Ethernet cable
- Soldering iron and some shrink tubes

## Setting up the Raspberry Pi
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

## Hooking up the sensors
### BME280
1. Solder the headers to the sensor PCB as shown in https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/assembly
2. Use four DuPont jumper wires to connect the sensor to the Raspberry Pi via I2C. (See "Raspberry Pi wired with I2C" on https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/python-circuitpython-test#python-computer-wiring-5-5. Color code and Pinout examples for RASPI 3 Model B:
- Pi *3V3* (PIN 1) to sensor *VIN*, red cable
- Pi *GND* (PIN 9) to sensor *GND*, Brown cable
- Pi *SCL* (GPIO 3, PIN 5) to sensor *SCK*, Orange cable
- Pi *SDA* (GPIO 2, PIN 3) to sensor *SDI*, Yellow cable

### Honeywell HPMA115S0
1. To make the wiring more straightforward, create a Molex-DuPont connector cable for the sensor. (Please see the [Datasheet](http://www.farnell.com/datasheets/2313714.pdf) for reference.)
- remove 4 cables from your 8 pin Molex pigtail (from right to left: pin 1, 3, 4 and 5)
- cut the DuPont connector from one end of 4 DuPont jumper wires
- splice the 4 remaining wires (pin 2, 6, 7 and 8) of your Molex pigtail to the jumper wires
2. Plug the Molex side of your connector cable to the sensor, and connect it to the Raspberry Pi via the following table:
- Pi *5V* (PIN 4) to sensor *Pin 2*, purple cable
- Pi *RXD* (GPIO 15, PIN 10) to sensor *Pin 6*, grey cable
- Pi *TXD* (GPIO 14, PIN 8) to sensor *Pin 7*, white cable
- Pi *GND* (PIN 4) to sensor *Pin 8*, black cable

## Testing the sensors
1. Boot up your Pi again, log in via SSH, and update it with the following command: **sudo apt-get update && sudo apt-get upgrade**
2. Install the Adafruit Python GPIO library: https://github.com/adafruit/Adafruit_Python_GPIO (check link for installation instructions)
3. Install the Adafruit BME280 library: https://github.com/adafruit/Adafruit_Python_BME280 (you can now use **git clone** command to install this library.)
4. Install the PySerial library: **pip install pyserial**
5. Install the ThingType HPMA115S0 library: https://github.com/ThingType/HPMA115S0_Python_library (use **git clone**; [Detailed documentation](https://thingtype.com/blog/using-an-hpma115s0-air-particles-sensor-with-a-raspberry-pi/))
6. Create a file (via **touch**) named `__init__`.py in the Adafruit_Python_BME280 and the HPMA115S0_Python directories, to make the importable in python. 
  - **Attention (status Aug 26 2018)**: The directory name HPMA115S0_Python_library has to be changed manually to HPMA115S0_Python.
7. Download the *sensortest.py* script from this repository to the directory, where the subfolders of the libraries are located. Run it, to check if everything works as expected: **python sensortest.py**

If you see valid data received from both sensors: congratulations, you've build yourself a sensor node!
