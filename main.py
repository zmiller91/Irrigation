__author__ = 'zmiller'

import serial
import requests
import json
import time
from datetime import datetime

def error(msg):
    print msg
    with open("err.txt", "a") as file:
        file.write(msg)
        file.write("\n")
        file.close()

def log(line):
    if printLog:
        print "--------------"
        print "len: " + str(line["length"])
        print "str: " + line["string"]
        print "--------------"

def post(line):
    out = {
        "date": str(datetime.now()),
        "method": "arduino_post",
        "values": line["string"]
    }
    out = json.dumps(out)
    response = requests.post(baseUrl, data=out)
    if response.status_code >= 400:
        e = {
            "status_code": response.status_code,
            "url": response.url,
            "post_body": out
        }
        e = json.dumps(e)
        error(e)

def get():
    # Get the arduino info from the database
    response = requests.get(baseUrl, {"method": "configuration", "arduino_id": arduinoId})
    if response.status_code == 200:
        response = response.json()
        conf = response["conf"]

        # Iterate over configuration object
        for component in conf:
            for action in conf[component]:

                # Replace the cache and write to the arduino if and only if the configuration is new
                change = False
                if component not in cache:
                    cache[component] = {}

                if action not in cache[component]:
                    cache[component][action] = {}

                if cache[component][action] != conf[component][action]:
                    cache[component][action] = conf[component][action]
                    change = True

                if change:
                    line = str(component) + ":" + str(action) + ":" + str(conf[component][action])
                    queue.append(line)

def now():
    return int(round(time.time() * 1000))

# baseUrl = "http://45.79.167. 160"
baseUrl = "http://localhost/Irrigation/public/index.php"
ser = serial.Serial('COM4', 9600, timeout=1)
printLog = True
sycEvery = 5
lastSync = -1
arduinoId = 2
cache = {}
queue = []
startTime = now()
while True:

    try:
        line = ser.readline().rstrip("\r\n")
        line = {"length": len(line), "string": line}

        # read any data coming from the arduino
        if line["length"] > 0:
            post(line)
            log(line)

        # write any data going to the arduino
        curSync = (now() - startTime) / 5000
        if lastSync <  curSync:
            lastSync = curSync
            get()

        time.sleep(1)
        if len(queue) > 0:
            s = queue.pop(0)
            print s
            ser.write(s)

    except Exception as e:
        error(str(e))
