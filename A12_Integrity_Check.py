#!/usr/bin/python3

'''
Author: @karngyan

Approach: I set up a public api that reponds to a GET call with data and its sha1

To check its integrity I will simply calculate the hash of the same and verify if its same or nor.

Code of the API: https://github.com/karngyan/data-hash-api
'''

import requests
import hashlib
import json

url = 'https://data-hash-api.karngyan.now.sh/dataWithHash'

response = requests.get(url).json()

data = response[0]['data']

remote_sha1_data = response[0]['sha1_of_data']

local_sha1_data = hashlib.sha1(data.encode()).hexdigest()

print('Local Sha1: ', local_sha1_data)
print('Remote Sha1: ', remote_sha1_data)

if (remote_sha1_data == local_sha1_data):
    print('\nSuccessfully verified data integrity.')
else:
    print('\nData integrity not successful')

'''
Output:
Local Sha1:  00cffe7312bf9ca73584f24bdf7df1d028340397
Remote Sha1:  00cffe7312bf9ca73584f24bdf7df1d028340397

Successfully verified data integrity.
'''