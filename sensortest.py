# Air quality monitoring with environmental sensors - testing the sensors
# Using the following libraries
#  - Adafruit_Python_BME280 by Adafruit - https://github.com/adafruit/Adafruit_Python_BME280
#  - HPMA115S0 library in Python by ThingType - https://github.com/ThingType/HPMA115S0_Python_library
# Tamas Halbrucker, 2018

from HPMA115S0_Python.HPMA115S0 import *
from Adafruit_Python_BME280.Adafruit_BME280 import *
import time

try:
    print("Aachen Air Quality Monitor v02 starting up...")

    sensor = BME280(t_mode=BME280_OSAMPLE_8, p_mode=BME280_OSAMPLE_8, h_mode=BME280_OSAMPLE_8)

    hpma115S0 = HPMA115S0("/dev/ttyS0")

    hpma115S0.init()
    hpma115S0.startParticleMeasurement()

    while 1:
        if (hpma115S0.readParticleMeasurement()):
            print("PM2.5    = %d ug/m3" % (hpma115S0._pm2_5))
            print("PM10     = %d ug/m3" % (hpma115S0._pm10))

            degrees = sensor.read_temperature()
            pascals = sensor.read_pressure()
            hectopascals = pascals / 100
            humidity = sensor.read_humidity()

            print("Temp     = {0:0.3f} deg C".format(degrees))
            print("Pressure = {0:0.2f} hPa".format(hectopascals))
            print("Humidity = {0:0.2f} %".format(humidity))
            print("-----------------------")

        time.sleep(1)

except KeyboardInterrupt:
    print(" Interrupt detected - Exiting.") 