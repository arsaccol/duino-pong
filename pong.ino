#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <assert.h>

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
    char received = getInput();
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
    Velocity velocity;

    void draw()
    {
        display.drawPixel(position.x, position.y, WHITE);
    }

    void update()
    {
        boundary_collision();
        position = Point
        {
            static_cast<int>(position.x + velocity.x),
            static_cast<int>(position.y + velocity.y)
        };
    }

    void boundary_collision()
    {
        Point possible_pos
        {
            static_cast<int>(position.x + velocity.x), 
            static_cast<int>(position.y + velocity.y)
        };

        if(possible_pos.x < 0 || possible_pos.x > SCREEN_WIDTH -1)
            velocity.x *= -1;
        if(possible_pos.y < 0 || possible_pos.y > SCREEN_HEIGHT - 1)
            velocity.y *= -1;
    }
};


struct Paddle
{
    Point position;

    void draw()
    {
        display.setCursor(position.x, position.y);
        // draw upwards and downwards...?
    }

    bool collide(Ball& ball)
    {
    }

    void update()
    {
    }


    
};

struct Game
{
    const int left{0};
    const int right{1};

    Paddle paddles[2] {{ Point{1, SCREEN_HEIGHT / 2 }}, { Point{SCREEN_WIDTH - 2, SCREEN_HEIGHT / 2} }};


    Game()
    {
    }
};


char getInput()
{
    if(Serial.available() > 0)
    {
        return Serial.read();
    }
}

Ball ball{{SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, {1.5f, 1.f}};


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
    
    ball.update();
    ball.draw();
    //printCharacter();
    delay(10);

    // End actual display code
    display.display();

}
