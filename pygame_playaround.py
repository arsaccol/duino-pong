import sys, pygame
import serial
import time

def main():
    size = width, height = 320, 240

    screen = pygame.display.set_mode(size)

    duino = serial.Serial('COM6', 9600)
    time.sleep(1)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT: sys.exit()
            #if event.type == pygame.MOUSEMOTION:
            #    x,y = pygame.mouse.get_pos()[0], pygame.mouse.get_pos()[1]

            #    print("Mouse position: ", str(x), str(y))
            if event.type == pygame.KEYDOWN:
                print(event.key)
                duino.write(bytearray([event.key]))

if __name__ == '__main__':
    main()
