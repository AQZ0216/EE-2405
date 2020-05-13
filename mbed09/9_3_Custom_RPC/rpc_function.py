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

s.write(bytes("/LEDControl/run 1 1\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/LEDControl/run 2 1\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/LEDControl/run 3 1\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/LEDControl/run 2 0\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/LEDControl/run 3 0\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)
time.sleep(1)

s.write(bytes("/LEDControl/run 1 0\r", 'UTF-8'))
line=s.readline() # Read an echo string from K66F terminated with '\n' (pc.putc())
print(line)
line=s.readline() # Read an echo string from K66F terminated with '\n' (RPC reply)
print(line)

s.close()