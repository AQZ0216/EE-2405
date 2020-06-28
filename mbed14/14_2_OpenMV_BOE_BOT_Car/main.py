import pyb
import sensor, image, time, math

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)  # must turn this off to prevent image washout...
sensor.set_auto_whitebal(False)  # must turn this off to prevent image washout...
clock = time.clock()

while(True):
   clock.tick()
   img = sensor.snapshot()
   img.lens_corr(1.8) # strength of 1.8 is good for the 2.8mm lens.

   matrices = img.find_datamatrices()
   for matrix in matrices:
      img.draw_rectangle(matrix.rect(), color = (255, 0, 0))
      print_args = (matrix.rows(), matrix.columns(), matrix.payload(), (180 * matrix.rotation()) / math.pi, clock.fps())
      uart.write(("Matrix [%d:%d], Payload \"%s\", rotation %f (degrees), FPS %f\r\n" % print_args).encode())
   if not matrices:
      uart.write(("FPS %f\r\n" % clock.fps()).encode())