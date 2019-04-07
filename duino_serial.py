#import serial.tools.list_ports as port_list
#
#ports = list(port_list.comports())
#for p in ports:
#    print(p)

import serial
import time
import datetime

duino = serial.Serial('COM3', 9600)
time.sleep(1)

while True:
    # use this encode function so the stupid Python strings
    # are converted into proper ASCII ones
    duino.write((str(datetime.datetime.now().isoformat(' ', 'seconds')) + '\n').encode())
    #duino.write(('lalala' + 'n').encode())
    time.sleep(1)
    print(datetime.datetime.now())

duino.close()
