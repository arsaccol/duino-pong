#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define NDEBUG

#define OLED_RESET 4

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int incomingByte = 0;

void printCharacter()
{
    //display.setTextSize(1);
    //display.setTextColor(WHITE);
    display.setCursor(1, SCREEN_HEIGHT / 2 - 1);
    //String received = Serial.readStringUntil('\n');
    //String received{getCharacter()};
    char received = getCharacter();
    //delay(10);
    //display.println(received);
    display.print(received);
}


void setCharacterPosition(int x, int y)
{
    display.setCursor(x, y);
}


struct Point
{
    Point(int x, int y)
        :   x{x}, y{y}
    {
        assert(x >= 0 && x < SCREEN_WIDTH && "Point position x must be between 0 and 128\n");
        assert(y >= 0 && y < SCREEN_HEIGHT && "Point position x must be between 0 and 32\n");
    }

    Point(const Point& other) = default;
    Point& operator=(const Point& other) = default;
    Point& operator=(const Point&& other) = default;

    
private:
    int x;
    int y;
};


struct Velocity
{
    float x;
    float y;
};


struct Ball
{
    Point position;
    char character;
};


struct Paddle
{
    Point position;

    void draw()
    {
    }

    bool collide(Ball& ball)
    {
    }

    
};


char getCharacter()
{
    if(Serial.available() > 0)
    {
        return Serial.read();
    }
}


void setup()
{
    Serial.begin(9600);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println(F("Couldn't begin serial"));
        for(;;);
    }

    display.display();
    delay(100);

    display.setTextSize(1);
    display.setTextColor(WHITE);
}


void loop()
{
    display.clearDisplay();
    // Actual display code here
    
    printCharacter();
    delay(10);

    // End actual display code
    display.display();

}
