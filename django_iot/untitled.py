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