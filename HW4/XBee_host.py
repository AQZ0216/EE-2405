import matplotlib.pyplot as plt
import numpy as np
import serial
import time
import paho.mqtt.client as paho
mqttc = paho.Client()

# Settings for connection
host = "localhost"
topic= "Mbed"
port = 1883

# Callbacks
def on_connect(self, mosq, obj, rc):
    print("Connected rc: " + str(rc))

def on_message(mosq, obj, msg):
    print("[Received] Topic: " + msg.topic + ", Message: " + str(msg.payload) + "\n");

def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed OK")

def on_unsubscribe(mosq, obj, mid, granted_qos):
    print("Unsubscribed OK")

# Set callbacks
mqttc.on_message = on_message
mqttc.on_connect = on_connect
mqttc.on_subscribe = on_subscribe
mqttc.on_unsubscribe = on_unsubscribe

# Connect and subscribe
print("Connecting to " + host + "/" + topic)
mqttc.connect(host, port=1883, keepalive=60)
mqttc.subscribe(topic, 0)

# XBee setting
serdev = '/dev/ttyUSB0'
s = serial.Serial(serdev, 9600)

s.write("+++".encode())
char = s.read(2)
print("Enter AT mode.")
print(char.decode())

s.write("ATMY 0x112\r\n".encode())
char = s.read(3)
print("Set MY 0x112.")
print(char.decode())

s.write("ATDL 0x212\r\n".encode())
char = s.read(3)
print("Set DL 0x212.")
print(char.decode())

s.write("ATID 0x1\r\n".encode())
char = s.read(3)
print("Set PAN ID 0x1.")
print(char.decode())

s.write("ATWR\r\n".encode())
char = s.read(3)
print("Write config.")
print(char.decode())

s.write("ATMY\r\n".encode())
char = s.read(4)
print("MY :")
print(char.decode())

s.write("ATDL\r\n".encode())
char = s.read(4)
print("DL : ")
print(char.decode())

s.write("ATCN\r\n".encode())
char = s.read(3)
print("Exit AT mode.")
print(char.decode())

print("start sending RPC")

t = np.arange(0,20,1)

n = np.arange(0,20,1)

s.write("/getReport/run\r".encode())
time.sleep(1)
char = s.read(1)
print(char)

for i in range(20):
    # send RPC to remote
    s.write("/getReport/run\r".encode())

    line=s.readline() # Read an echo string from K66F terminated with '\n'
    print(line)
    n[i] = float(line)

    time.sleep(1)

s.write("/getRecord/run\r".encode())

for i in range(40):
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    mqttc.publish(topic, line)
    print(line)
    float(line)
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    mqttc.publish(topic, line)
    print(line)
    float(line)
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    mqttc.publish(topic, line)
    print(line)
    z = float(line)

    if z < 0.707:
        line = "1\r\n".encode()
    else:
        line = "0\r\n".encode()

    mqttc.publish(topic, line)

    time.sleep(0.1)

plt.plot(t, n, color="blue", label="n")
plt.xlabel('Time')
plt.ylabel('Acc Vector')
plt.show()
s.close()