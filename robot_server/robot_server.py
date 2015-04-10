#!/usr/bin/env python
import serial
import struct
import thread
from base64 import b64encode, b64decode
from discover_addr import handshake

from socket import socket, AF_INET, SOCK_DGRAM


class BaseConn(object):
	packet_format = None
	_lock = thread.allocate_lock()

	def __init__(self):
		self.conn = self.create_conn()

		self.callbacks = []

		self._thread = None
		self._size = struct.calcsize(self.packet_format)

	def create_conn(self):
		pass

	def readline(self):
		pass

	def writeline(self):
		pass

	def start(self):
		self._thread = thread.start_new_thread(self.tick, ())

	def tick(self):
		while True:
			data = self.readline()
			data_unpacked = struct.unpack(self.packet_format, data)
			for calbk in self.callbacks:
				with self._lock:
					calbk(data_unpacked)

	def bind(self, func):
		self.callbacks.append(func)


class NetworkConn(BaseConn):
	packet_format = 'ffff'
	def __init__(self):
		self.addr = handshake()
		super(self.__class__, self).__init__()

	def create_conn(self):
		conn = socket(AF_INET, SOCK_DGRAM)
		conn.bind(('', 4444))

		return conn

	def readline(self):
		return self.conn.recv(self._size)

	def writeline(self, data):
		conn.sendto(data, (self.addr, 4444))


class ArduinoConn(BaseConn):
	packet_format = 's'
	def create_conn(self):
		return serial.Serial('/dev/ttyACM0', 115200)

	def readline(self):
	 	return b64decode(self.conn.readline())

	def writeline(self, data):
		self.conn.write(b64encode(data))

def _a_print(stuff):
	print "Arduino: ", stuff


def _n_print(stuff):
	print "Network: ", stuff


nconn = NetworkConn()
nconn.bind(_n_print)
nconn.start()

aconn = ArduinoConn()
aconn.bind(_a_print)
def _write_a_data(data):
	aconn.writeline(struct.pack('ffff', *data))
nconn.bind(_write_a_data)
aconn.start()

nconn.writeline('Foo')

print "Enter to quit."
raw_input()
