import socket
import time

UDP_IP = "127.0.0.1"
UDP_PORT = 9050
 
print "UDP target IP:",   UDP_IP
print "UDP target port:", UDP_PORT

counter=0;
 
sock = socket.socket(socket.AF_INET,     # Internet protocol
                     socket.SOCK_DGRAM)  # User Datagram (UDP)
while True:
    #Make string to send as UDP
    counter+=1
    Message= "My UDP Message nr: " + str(counter);

    # Send the message
    sock.sendto(Message, (UDP_IP, UDP_PORT)) 

    #Wait a second before retansmitting data
    time.sleep(1) 

