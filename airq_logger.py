# Air quality monitoring with environmental sensors - stand-alone logger
# Using the following libraries
#  - Adafruit_Python_BME280 by Adafruit - https://github.com/adafruit/Adafruit_Python_BME280
#  - HPMA115S0 library in Python by ThingType - https://github.com/ThingType/HPMA115S0_Python_library
# Tamas Halbrucker, 2018

# importing the necessary libraries
from HPMA115S0_Python.HPMA115S0 import *
from Adafruit_Python_BME280.Adafruit_BME280 import *
import time
import datetime

try:
    print("Aachen Air Quality Logger v01 starting up...")

    filename = "logger_" + datetime.datetime.now().strftime("%Y%m%d_%H%M%S") + ".csv"

    print("Creating the output file: " + filename)

    # Creating the output file and writing the header
    f = open(filename,"w+", 1)
    headerrow = "timestamp (YYYY-MM-DD_HH:mm:SS),PM2.5 (ug/m3),PM10 (ug/m3),temperature (deg C),pressure (hPa),humidity (%)\n"
    f.write(headerrow)

    # creating the sensor objects
    sensor = BME280(t_mode=BME280_OSAMPLE_8, p_mode=BME280_OSAMPLE_8, h_mode=BME280_OSAMPLE_8)

    hpma115S0 = HPMA115S0("/dev/ttyS0")

    # initializing the Honeywell sensor
    hpma115S0.init()
    hpma115S0.startParticleMeasurement()

    # infinite loop
    while 1:
        # checking every second if we have valid data available
        if (hpma115S0.readParticleMeasurement()):
            # reading out the sensors
            pm2_5 = hpma115S0._pm2_5
            pm10 = hpma115S0._pm10
            degrees = sensor.read_temperature()
            pascals = sensor.read_pressure()
            hectopascals = pascals / 100
            humidity = sensor.read_humidity()

            # printing the results
            print("PM2.5    = %d ug/m3" % (pm2_5))
            print("PM10     = %d ug/m3" % (pm10))
            print("Temp     = {0:0.3f} deg C".format(degrees))
            print("Pressure = {0:0.2f} hPa".format(hectopascals))
            print("Humidity = {0:0.2f} %".format(humidity))
            print("-----------------------")
	
            # writing the results to the output file
            datarow = datetime.datetime.now().strftime("%Y-%m-%d_%H:%M:%S") + "," + str(pm2_5) + "," + str(pm10) + "," + "{0:0.3f}".format(degrees) + "," + "{0:0.2f}".format(hectopascals) + "," + "{0:0.2f}".format(humidity) + "\n"
            f.write(datarow)

            # sleep until the next run
            time.sleep(0.979)

except KeyboardInterrupt:
    # closing the output file when done
    f.close()
    print(" Interrupt detected - Exiting.")