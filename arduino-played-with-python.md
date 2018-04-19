---
title: arduino played with python
date: 2018-04-19 23:21:35
tags: python_arduino
---

## 使用pyserial进行串口通信

```
pip install pyserial
```

对，就这样，不用去下什么复杂的api，前期简单用用不必那么麻烦。能读出来数据就行。

然后这么玩

```
import time
import serial

ser = serial.Serial( #下面这些参数根据情况修改
    port='/dev/ttyACM0',
    baudrate=9600,
    parity=serial.PARITY_ODD,
    stopbits=serial.STOPBITS_TWO,
    bytesize=serial.SEVENBITS
)
data = ''


while True:
    data = ser.readline()
    data = data.decode('UTF-8')
    print(data)
```

解释下倒数第二行，从串口读出来的数据是byte型的，要想让套用str方法之类的，我们需要转码，也就是decode。

我一开始写的是 data = str(data)

···

2333

然后调用restful api其实很简单。

用requests模块post过去就行。



```
#test_untitled.py
import json
import requests

suck = '19'
def test_post_temp():
	# read the sensor to determine the post or not
	json_data = dict(
		led13 = 'true',
		temperature = suck
		)
	
	rsp = requests.post(url ='http://localhost:8000',  headers={
        'Accept': 'application/json',
        'Content-Type': 'application/json',
    	}, data=json.dumps(json_data))
    
	#print(json.dumps(json_data))
	return rsp

test_post_temp()
```

简单吧。



之后怎么写明天再做笔记。