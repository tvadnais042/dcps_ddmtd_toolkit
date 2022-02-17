#!/usr/bin/python
# coding=utf-8

import RPi.GPIO as GPIO
from time import sleep


GPIO.setmode(GPIO.BCM)
GPIO.setup(19,GPIO.OUT)




GPIO.output(19,0)

sleep(1)


GPIO.cleanup()
