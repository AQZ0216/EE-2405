import numpy as np
import serial
import time

waitTime = 0.1

# generate the waveform table
signalLength = [20, 19, 42]
signalTable = [[311, 330, 370, 494, 554, 494,
  494, 466, 370, 330, 330,
  330, 311, 247, 330, 311,
  277, 247, 311, 247],
  [784, 523, 659, 494, 523, 659, 440,
  523, 659, 392, 440, 523, 440, 
  523, 392, 523, 659, 523, 587],
  [261, 261, 392, 392, 440, 440, 392,
  349, 349, 330, 330, 294, 294, 261,
  392, 392, 349, 349, 330, 330, 294,
  392, 392, 349, 349, 330, 330, 294,
  261, 261, 392, 392, 440, 440, 392,
  349, 349, 330, 330, 294, 294, 261]]
noteLength = [[1, 1, 1, 1, 2, 2,
  2, 1, 1, 2, 2,
  2, 1, 1, 2, 2,
  2, 1, 1, 2],
  [2, 1, 1, 2, 1, 1, 2,
  1, 1, 2, 1, 1, 3,
  1, 3, 1, 3, 1 ,4],
  [1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 2,
  1, 1, 1, 1, 1, 1, 2]]

# output formatter
formatter = lambda x: "%.3f" % x

# send the waveform table to K66F
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)
while(1):
  line=s.readline() # Read an echo string from K66F terminated with '\n'
  # print line
  index = line[0]-48
  print(line)

  print("Sending signal ...")
  print("It may take about %d seconds ..." % (int(signalLength[index] * waitTime * 2)))
  for data in signalTable[index]:
    s.write(bytes(formatter(data), 'UTF-8'))
    time.sleep(waitTime)
  for data in noteLength[index]:
    s.write(bytes(formatter(data), 'UTF-8'))
    time.sleep(waitTime)
  print("Signal sended")
s.close()