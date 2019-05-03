#import serial.tools.list_ports as port_list
#
#ports = list(port_list.comports())
#for p in ports:
#    print(p)

import serial
import time
import datetime
import keyboard

duino = serial.Serial('COM', 9600)
time.sleep(1)

while True:
    # use this encode function so the stupid Python strings
    # are converted into proper ASCII ones
    #duino.write((str(datetime.datetime.now().isoformat(' ', 'seconds')) + '\n').encode())
    #duino.write(('lalala' + 'n').encode())

    #for key_press in keyboard._pressed_events:
    #    print(str(key_press))
    #    duino.write(bytes(key_press))

    #duino.write(bytes('x')str.encode('ascii'))
    duino.write(bytearray([ord('a'), ord('b'), ord('c'), ord('d'), ord('5')]))
    #duino.write(bytearray([ord('a')]))



duino.close()
