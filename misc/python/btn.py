#!/usr/bin/env python

import os
import sys
import subprocess

if not os.getegid() == 0:
    sys.exit('Script must be run as root')

from time import sleep
from subprocess import *
from pyA20.gpio import gpio
from pyA20.gpio import connector
from pyA20.gpio import port


button_shutdown = port.PA2  #PIN 20

"""Init gpio module"""
gpio.init()

"""Set directions"""
gpio.setcfg(button_shutdown, gpio.INPUT)


"""Enable pullup resistor"""
gpio.pullup(button_shutdown, gpio.PULLUP)

def delay_milliseconds(milliseconds):  
    seconds = milliseconds / float(1000)
    sleep(seconds)  

def run_cmd(cmd):  
   p = Popen(cmd, shell=True, stdout=PIPE, stderr=STDOUT)  
   output = p.communicate()[0]  
   return output  

shutdown_pressed = 1
while True:
   value_out = 0
   shutdown_pressed = gpio.input(button_shutdown)

   if (shutdown_pressed == 0):
      value_out = 1
      run_cmd("shutdown now")

   delay_milliseconds(100)
