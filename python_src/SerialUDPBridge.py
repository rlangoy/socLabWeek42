import serial #Serial port API http://pyserial.sourceforge.net/pyserial_api.html
import socket
import time

port = "/dev/ttyACM0"

UDP_IP = "127.0.0.1"
UDP_PORT = 9050
 
print "UDP target IP:",   UDP_IP
print "UDP target port:", UDP_PORT

sock = socket.socket(socket.AF_INET,     # Internet protocol
                     socket.SOCK_DGRAM)  # User Datagram (UDP)

SerialIOArduino = serial.Serial(port,9600) #setup the serial port and baudrate
SerialIOArduino.flushInput() #Remove old input's

while True:
    if (SerialIOArduino.inWaiting() > 0):
        inputLine = SerialIOArduino.readline().strip()  # read a '\n' terminated line()

        # Send the csv string as a UDP message
        sock.sendto(inputLine, (UDP_IP, UDP_PORT))

