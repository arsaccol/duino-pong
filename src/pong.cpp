#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <assert.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define NDEBUG

#define OLED_RESET 4

TwoWire led_tw, mpu_tw;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &led_tw, OLED_RESET);

char getInput();

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


struct Rectangle
{
    Point position;
    Point size;
    
    void draw(Adafruit_SSD1306 drawingDevice)
    {
        for(int i = 0; i < size.y; ++i)
        {
            //display.(position.x, position.y + i, size.x);
            drawingDevice.drawLine(position.x, position.y + i, position.x + size.x, position.y + i, DISPLAY);
        }
    }

    bool contains(Point point)
    {
        if(point.x >= position.x && point.x <= position.x + size.x)
        {
            if(point.y >= position.y && point.y <= position.y + size.y)
                return true;
            else return false;
        }
        else return false;
    }

    bool is_there_overlap(Rectangle& otherRect)
    {
        // Negate conditions in which there is NO overlap
        if (!(
            position.x + size.x < otherRect.position.x || 
            position.x > otherRect.position.x + otherRect.size.y||
            position.y + size.y < otherRect.position.y + otherRect.size.y||
            position.y > otherRect.position.y + otherRect.size.y
        ))
            return true;
        else
            return false;
    }

};


struct Velocity
{
    float x;
    float y;
};


struct Ball : public Rectangle 
{
    Velocity velocity;

    Ball(Point position = {SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2}, Velocity = {0.f, 0.f})
        :   Rectangle{position, {2, SCREEN_HEIGHT / 32}}
        ,   velocity{velocity}
    {
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

        if(possible_pos.x < 0 || possible_pos.x + size.x > SCREEN_WIDTH -1)
            velocity.x *= -1;
        if(possible_pos.y < 0 || possible_pos.y + size.y > SCREEN_HEIGHT - 1)
            velocity.y *= -1;
    }
};



struct Paddle : public Rectangle
{

    Paddle(Point position, Point size = {2, 8})
        :   Rectangle{position, size}
    {
        //this->position = position;
        //this->size = size;
    }


    bool collide(Ball& ball)
    {
        return false;
    }

    void update()
    {
    }


    
};

struct Player
{
    enum class Type
    {
        Human,
        Computer
    };

    Type type;
    Paddle& controlled_paddle;

    Player(Paddle& controlled_paddle, Player::Type playerType)
        :   controlled_paddle{controlled_paddle}
    {}

    void update()
    {
        if(type == Type::Human)
            humanUpdate();
        else if(type == Type::Computer)
            computerUpdate();

    }

    void humanUpdate()
    {
        char input = getInput();
        if(input == 'w')
            controlled_paddle.position.y -= 5;
        else if(input == 's')
            controlled_paddle.position.y += 5;
    }


    void computerUpdate()
    {
        controlled_paddle.position.y = rand() % SCREEN_HEIGHT;
    }
};


struct Game
{
    enum PaddleID
    {
        left = 0,
        right = 1,
        numPaddles
    };

    bool running{true};

    Paddle paddles[numPaddles] {{ Point{1, SCREEN_HEIGHT / 2 }}, { Point{SCREEN_WIDTH - 2, SCREEN_HEIGHT / 2} }};
    Player players[numPaddles] {Player{paddles[left], Player::Type::Human}, Player{paddles[right], Player::Type::Computer}};
    Ball ball{};


    Game()
    {
        ball.velocity = {2.f, -1.f};
    }

    void loop_frame()
    {
        while(running)
        {
            update();
            draw();
            delay(16);
        }
    }

    void update()
    {
        players[left].update();
        players[right].update();
        ball.update();

    }

    void draw()
    {
        display.clearDisplay();
        paddles[left].draw(display);
        paddles[right].draw(display);
        ball.draw(display);

        display.display();
    }

};


char getInput()
{
    if(Serial.available() > 0)
    {
        return Serial.read();
    }
    else
        return '\0';
}

Game game;

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
    game.loop_frame();
}
