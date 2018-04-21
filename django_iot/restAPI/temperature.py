# -*- coding: UTF-8 -*-

import time
import serial
import pdb
import json
import requests

class GetData(object):
	"""docstring for base_once_post"""
	def __init__(self):
		self.flag = False
		self.readsensor = ''
		self.ser = serial.Serial( #下面这些参数根据情况修改
			port='/dev/ttyACM2',
			baudrate=9600,
			parity=serial.PARITY_ODD,
			stopbits=serial.STOPBITS_TWO,
			bytesize=serial.SEVENBITS
		)
	
	def update():
		pass

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



		
def judge_select_data(orgin, after):
	#三目运算符的python写法，这玩意真的支持中文啦啦啦，贼开心
	#https://www.cnblogs.com/afei-qwerty/p/6710235.html sublime_text3_linux中文支持
	return False if after == orgin else True

def loop(flag, readsensor, ser):
	while True:
		data_lamba = GetData()
		data = ser.readline()
		data = data.decode('UTF-8')
		print(data)
		#print(flag, 'was')
		if data[:13] == 'Read sensor: ':
			if data[13:15] == 'OK':
				flag = True
		if flag:
			if data[:4] == 'Temp':
				#print(1)
				flag = False
				if judge_select_data(readsensor, data[-7:]):
					readsensor = data[-7:]
					print(readsensor)
					data_lamba.test_post_temp(readsensor)

			
	#analyze the data and divide it post to the web
if __name__ == '__main__':
	Data = GetData()
	loop(Data.flag, Data.readsensor, Data.ser)