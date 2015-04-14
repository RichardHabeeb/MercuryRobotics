#!/usr/bin/env python
#--------------------------------------------------------------------------------------------------
# Kansas State University Robotic Competition Team
# robot_server.py
#--------------------------------------------------------------------------------------------------

#------------------------------------------------
# Imports
#------------------------------------------------
import serial
import thread
import struct
import base64
import time
from discover_addr import handshake
from socket import socket, AF_INET, SOCK_DGRAM

#-----------------------------------------------
# Parameters
#-----------------------------------------------
motor_packet_string = "ffffI"
sensor_packet_string = "ffff"
baseStationListener = socket(AF_INET, SOCK_DGRAM)
baseStationListener.bind(('', 4444))
baseStationSender = socket(AF_INET, SOCK_DGRAM)
baseStationIP = ""
quitThreads = False
arduino = None#serial.Serial('/dev/ttyACM0', 115200)

#-----------------------------------------------
# Functions
#-----------------------------------------------
def main():
	print "Waiting for BaseStation IP Address..."
	while(True):
		baseStationIP = baseStationListener.recv(16)
		if(len(baseStationIP) > 0):
			break
	print "Connected to ", baseStationIP, "\nStarting threads..."
	thread.start_new_thread(wait_motor_packet, ())
	thread.start_new_thread(wait_sensor_packet, tuple([baseStationIP]))
	print "Press enter to quit."
	raw_input() or ""
	quitThreads = True
		
	
def wait_motor_packet():
	while(not quitThreads):
		data = baseStationListener.recv(struct.calcsize(motor_packet_string))
		if(len(data) == struct.calcsize(motor_packet_string)):
			#arduino.write(base64.b64encode(data))
			print "Recieved motor packet ", struct.unpack(motor_packet_string, data)

def wait_sensor_packet(ip):
	while(not quitThreads):
		#data = arduino.readline()
		data = "MTIzNDEyMzQxMjM0MTIzNA=="
		time.sleep(1)
		if(len(data) == 24):
			baseStationSender.sendto(base64.b64decode(data), (ip, 4445))
			print "Sending sensor packet to ", ip, struct.unpack(sensor_packet_string, base64.b64decode(data))

#-----------------------------------------------
# Initialization
#-----------------------------------------------
main()
