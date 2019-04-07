#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void printCharacter(char character)
{
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(1, SCREEN_HEIGHT / 2 - 1);
    //String received = Serial.readString();
    String received = Serial.readStringUntil('\n');
    delay(1000);
    display.println(received);
}

char incrementing_character = 'A';

void setup()
{
    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("Couldn't begin serial"));
        for(;;);
    }

    display.display();
    delay(500);

}

void loop()
{
    display.clearDisplay();
    // Actual display code here
    
    printCharacter(incrementing_character);

    // End actual display code
    display.display();

}
