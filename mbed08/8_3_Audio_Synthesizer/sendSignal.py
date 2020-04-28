import numpy as np
import serial
import time

waitTime = 0.1

# generate the waveform table
signalLength = 1024
t = np.linspace(0, 2*np.pi, signalLength)
signalTable = (np.sin(t) + 1.0) / 2.0 * ((1<<16) - 1)

# output formatter
formatter = lambda x: "%.3f" % x

# send the waveform table to K66F
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
print("Sending signal ...")
print("It may take about %d seconds ..." % (int(signalLength * waitTime)))
for data in signalTable:
  s.write(bytes(formatter(data), 'UTF-8'))
  time.sleep(waitTime)
s.close()
print("Signal sended")