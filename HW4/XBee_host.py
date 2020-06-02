import matplotlib.pyplot as plt
import numpy as np
import serial
import time

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

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev, 115200)
for i in range(100):
    # send RPC to remote
    s.write("/getReport/run\r".encode())
    time.sleep(1)

    line=s.readline() # Read an echo string from K66F terminated with '\n'
    # print line
    n[i] = float(line)

plt.plot(t, n, color="blue", label="n")
plt.set_xlabel('Time')
plt.set_ylabel('Acc Vector')
plt.show()
s.close()