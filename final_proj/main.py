import pyb
import sensor, image, time, os, tf, math

uart = pyb.UART(3,9600,timeout_char=1000)
uart.init(9600,bits=8,parity = None, stop=1, timeout_char=1000)
tmp = ""

def image_classification():
    sensor.reset()                         # Reset and initialize the sensor.
    sensor.set_pixformat(sensor.RGB565)    # Set pixel format to RGB565 (or GRAYSCALE)
    sensor.set_framesize(sensor.QVGA)      # Set frame size to QVGA (?x?)
    sensor.set_windowing((240, 240))       # Set 240x240 window.
    sensor.skip_frames(time=2000)          # Let the camera adjust.

    labels = ['3', '4', '0', 'other']

    img = sensor.snapshot()

    for obj in tf.classify('/model_demo.tflite',img, min_scale=1.0, scale_mul=0.5, x_overlap=0.0, y_overlap=0.0):
      img.draw_rectangle(obj.rect())
      img.draw_string(obj.x()+3, obj.y()-1, labels[obj.output().index(max(obj.output()))], mono_space = False)

    RED_LED_PIN = 1
    BLUE_LED_PIN = 3

    sensor.reset() # Initialize the camera sensor.
    sensor.set_pixformat(sensor.RGB565) # or sensor.GRAYSCALE
    sensor.set_framesize(sensor.QVGA) # or sensor.QQVGA (or others)
    sensor.skip_frames(time = 2000) # Let new settings take affect.

    pyb.LED(RED_LED_PIN).on()
    sensor.skip_frames(time = 2000) # Give the user time to get ready.

    pyb.LED(RED_LED_PIN).off()
    pyb.LED(BLUE_LED_PIN).on()

    print("You're on camera!")
    sensor.snapshot().save("example.jpg") # or "example.bmp" (or others)

    pyb.LED(BLUE_LED_PIN).off()
    print("Done! Reset the camera to see the saved image.")

    return labels[obj.output().index(max(obj.output()))]

def datamatrix():
    sensor.reset()                         # Reset and initialize the sensor.
    sensor.set_pixformat(sensor.RGB565)    # Set pixel format to RGB565 (or GRAYSCALE)
    sensor.set_framesize(sensor.QVGA)      # Set frame size to QVGA (?x?)
    sensor.skip_frames(time=2000)          # Let the camera adjust.
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
    return

while(1):
    a = uart.readline()
    if a is not None:
        tmp += a.decode()
        print(a.decode())

    if tmp == "image_classification":
        print("classify images")
        tmp =""
        label = image_classification()
        print(label)
        uart.write(label.encode())

    if tmp == "datamatrix":
        print("datamatrix")
        tmp =""
        datamatrix()
