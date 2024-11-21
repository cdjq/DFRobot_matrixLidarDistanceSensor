# -*- coding: utf-8 -*-
"""
@file get_all_data.py
@brief This is a demo to retrieve all matrix data. Running this code will print the matrix data.
@copyright  Copyright (c) 2024 DFRobot Co.Ltd (http://www.dfrobot.com)
@license     The MIT License (MIT)
@author [tangjie](jie.tang@dfrobot.com)
@version  V1.0
@date  2024-09-9
@url https://github.com/DFRobot/DFRobot_matrixLidarDistanceSensor
"""

from __future__ import print_function
import sys
import os
sys.path.append("../")
import time

from DFRobot_matrixLidarDistanceSensor import *

ADDRESS = 0x30

# I2C mode
tof = DFRobot_matrixLidarDistanceSensor_I2C(ADDRESS)

#uart mode
#tof = DFRobot_matrixLidarDistanceSensor_UART()

def setup():
  while tof.begin() != 0:
    print("begin error!!!!")
    time.sleep(1)
  while tof.get_all_data_config(4) != 0:
    print("init error")
    time.sleep(1)
    

def loop():
  data = tof.get_all_data()
  for index in range(0, len(data), 2):
    high_byte = data[index + 1]
    low_byte = data[index ]
    combined_value = (high_byte << 8) | low_byte 
    print(combined_value, end=' ')
    if (index // 2 + 1) % 4 == 0:
      print() 
  print("-------------------")
  time.sleep(1)
  
    
if __name__ == "__main__":
  setup()
  while True:
    loop()