import matplotlib.pyplot as plt
import numpy as np
import serial
import time

t = np.arange(0,10,0.1)

x = np.arange(0,10,0.1)
y = np.arange(0,10,0.1)
z = np.arange(0,10,0.1)
tilt = np.arange(0,10,0.1)

serdev = '/dev/ttyACM0'
s = serial.Serial(serdev, 115200)
for i in range(100):
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    # print line
    x[i] = float(line)
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    # print line
    y[i] = float(line)
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    # print line
    z[i] = float(line)
    line=s.readline() # Read an echo string from K66F terminated with '\n'
    # print line
    tilt[i] = float(line)

fig, ax = plt.subplots(2, 1)
ax[0].plot(t, x, color="blue", label="x")
ax[0].plot(t, y, color="red", label="y")
ax[0].plot(t, z, color="green", label="z")
ax[0].set_xlabel('Time')
ax[0].set_ylabel('Acc Vector')
ax[0].legend(loc='lower left')
ax[1].stem(t, tilt)
ax[1].set_xlabel('Time')
ax[1].set_ylabel('Tilt')
plt.show()
s.close()