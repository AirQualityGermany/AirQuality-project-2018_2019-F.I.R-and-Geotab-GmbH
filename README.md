# Cooperation-RWTH-and-Geotab
Repository created to host any SW development activities around the Air Quality project between f.i.r and Geotab

# Building the sensor node
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
3. Create an empty file named "ssh" on the boot partition of the microSD card (to enable the SSH server)
4. Plug the microSD card in the Raspberry Pi, connect it via Ethernet to your local network, and power it up using the microUSB cable
5. After it's booted up, connect to the Pi via SSH (with an SSH client like [PuTTY](https://www.putty.org/)). To find out the Pi's IP address, please check the DHCP clients on your routers admin page. The default user/pass of the Pi is pi/raspberry.
6. If you've successfully logged in, please configure your Pi with the [raspi-config](https://www.raspberrypi.org/documentation/configuration/raspi-config.md) tool: **sudo raspi-config**. It's important to:
  - change the user password
  - set a unique hostname
  - set up the WLAN network
  - set the correct time zone and WiFi country
  - configure the necessary interfaces (SSH is already enabled, I2C needs to be turned on, shell output on the Serial interface needs to be *disabled*)
  - expand the file system
7. If you're done with the configuration, restart the Pi with **sudo reboot now**. Check if all the changes are correct, then shut down it with **sudo shutdown now**, and remove the power cable.

## Hooking up the sensors
### BME280
1. Solder the headers to the sensor PCB as shown in https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/assembly
2. Use four DuPont jumper wires to connect the sensor to the Raspberry Pi via I2C. (See "Raspberry Pi wired with I2C" on https://learn.adafruit.com/adafruit-bme280-humidity-barometric-pressure-temperature-sensor-breakout/python-circuitpython-test#python-computer-wiring-5-5. Color code and Pinout examples for RASPI 3 Model B:
- Pi *3V3* to sensor *VIN* (PIN 1, red cable)
- Pi *GND* to sensor *GND* (PIN 9, Brown cable)
- Pi *SCL* (GPIO 3) to sensor *SCK* (PIN 5, Orange cable)
- Pi *SDA* (GPIO 2) to sensor *SDI* (PIN 3, Yellow cable)

### Honeywell HPMA115S0
1. To make the wiring more straightforward, create a Molex-DuPont connector cable for the sensor. (Please see the [Datasheet](http://www.farnell.com/datasheets/2313714.pdf) for reference.)
- remove 4 cables from your 8 pin Molex pigtail (from right to left: pin 1, 3, 4 and 5)
- cut the DuPont connector from one end of 4 DuPont jumper wires
- splice the 4 remaining wires (pin 2, 6, 7 and 8) of your Molex pigtail to the jumper wires
2. Plug the Molex side of your connector cable to the sensor, and connect it to the Raspberry Pi via the following table:
- Pi *5V* to sensor *Pin 2*
- Pi *RXD* (GPIO 15) to sensor *Pin 6*
- Pi *TXD* (GPIO 14) to sensor *Pin 7*
- Pi *GND* to sensor *Pin 8*

## Testing the sensors
1. Boot up your Pi again, log in via SSH, and update it with the following command: **sudo apt-get update && sudo apt-get upgrade**
2. Install the Adafruit Python GPIO library: https://github.com/adafruit/Adafruit_Python_GPIO
3. Install the Adafruit BME280 library: https://github.com/adafruit/Adafruit_Python_BME280
4. Install the PySerial library: **pip install pyserial**
5. Install the ThingType HPMA115S0 library: https://github.com/ThingType/HPMA115S0_Python_library ([Detailed documentation](https://thingtype.com/blog/using-an-hpma115s0-air-particles-sensor-with-a-raspberry-pi/))
6. Download the *sensortest.py* script from this repository and run it, to check if everything works as expected: **python sensortest.py**

If you see valid data received from both sensors: congratulations, you've build yourself a sensor node!
