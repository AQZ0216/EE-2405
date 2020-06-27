import pyb
import sensor, image, time, os, tf

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)
tmp = ""

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must turn this off to prevent image washout...
clock = time.clock()

while(1):
   a = uart.readline()
   if a is not None:
      tmp += a.decode()
      print(a.decode())

   if tmp == "image_classification":
      print("classify images")
      tmp =""
      while(True):
         clock.tick()
         img = sensor.snapshot()
         img.lens_corr(1.8) # strength of 1.8 is good for the 2.8mm lens.
         for code in img.find_qrcodes():
            img.draw_rectangle(code.rect(), color = (255, 0, 0))
            print(code)
            uart.write(("%s\r\n" % code.payload()).encode())

         uart.write(("FPS %f\r\n" % clock.fps()).encode())
         print(clock.fps())
