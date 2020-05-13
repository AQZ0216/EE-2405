import serial
import time
serdev = '/dev/ttyACM0'
s = serial.Serial(serdev)

s.write(bytes("\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/doDisplay/run IMR \r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)


s.write(bytes("/doLocate/run 8 0\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/doDisplay/run WELL\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)