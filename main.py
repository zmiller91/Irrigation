__author__ = 'zmiller'

import serial
import requests
import json
from time import sleep
from datetime import datetime

ser = serial.Serial('/dev/ttyACM0', 9600)
while True:

    try:
        dt = str(datetime.now())

        out = {
            "date": str(datetime.now()), 
            "method": "arduino_post", 
            "values": ser.readline().rstrip("\r\n")
        }

        out = json.dumps(out)
        requests.post("http://45.79.167.160", data=out)
        print out
        sleep(0.1)
    except Exception as e:
        with open("err.txt", "a") as file:
            file.write(e);
            file.write("\n");
            file.close();
