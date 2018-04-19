# -*- coding: UTF-8 -*-

import time
import serial

import json
import requests

BASE_URL = 'http://localhost:8000'
AUTH = ('admin', 'admin')

def test_post_temp(readsensor):
	# read the sensor to determine the post or not
	json_data = dict(
		temperature = readsensor
		)
	rsp = requests.post(url ='http://localhost:8000',  headers={
        'Accept': 'application/json',
        'Content-Type': 'application/json',
    	}, data=json.dumps(json_data))
	return rsp
		

ser = serial.Serial( #下面这些参数根据情况修改
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)
data = ''

#做模块化

while True:
    data = ser.readline()
    data = data.decode('UTF-8')
    print(data)
    #analyze the data and divide it post to the web
