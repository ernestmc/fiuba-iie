import serial
import numpy as np
from matplotlib import pyplot as plt

uart = serial.Serial("/dev/ttyACM0", 57600)
uart.close()
uart.open()

plt.ion()
ydata = [0] * 50
ax1 = plt.axes()

# make plot
line, = plt.plot(ydata)
plt.ylim([-5, 260])


while True:
    num_bytes = uart.inWaiting()
    if num_bytes > 0:
        data = uart.read(num_bytes)
        bytes = []
        for d in data:
            bytes.append(ord(d))
        print len(ydata), num_bytes
        del ydata[0:num_bytes]
        print len(ydata)
        ydata += bytes
        line.set_xdata(np.arange(len(ydata)))
        line.set_ydata(ydata)  # update the data
        plt.draw()  # update the plot


uart.close()
