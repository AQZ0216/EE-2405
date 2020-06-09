import matplotlib.pyplot as plt
import numpy as np
import serial

Ts = 30;   # signal interval
end = 150; # signal end point
n = int(end/Ts)+1

x = np.linspace(0, end, num=n) # x axis
y = np.zeros(n)                # y axis

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)

for i in range(0, n):
    line=s.readline() # Read a string from K66F terminated with '\n'
    print (line)
    y[i] = float(line)

plt.figure()
plt.plot(x,y)
plt.xlabel('signal')
plt.ylabel('speed (cm/sec)')
plt.show()
s.close()