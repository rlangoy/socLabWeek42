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
    #Make a 3 bit counter
    counter=(counter+1)%8
    aBinCnt=bin(counter)[2:].zfill(3)

    #Make a csv string 
    Message= "$SW,"+aBinCnt[2]+","+aBinCnt[1]+","+aBinCnt[0]

    # Send the csv string as a UDP message
    sock.sendto(Message, (UDP_IP, UDP_PORT))

    print "Sendt Message: "+Message

    #Wait a second before retansmitting data
    time.sleep(1) 

