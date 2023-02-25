#include <SFML/Graphics.hpp>
#include "board&pawns.h"

#define WIDTH 1200     // window size
#define HEIGHT 950

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ludo", sf::Style::Titlebar | sf::Style::Close);     // window
sf::CircleShape shape1(8), shape2(8), shape3(8), shape4(8), shape5(8), shape6(8), shape7(8), shape8(16);     // circles
sf::RectangleShape square, button;     // rectangles
sf::Event event;     // key i mouse
sf::Font font, font1;     // fonts
Board b[3], y[3], g[3], r[3], p[32], f[16];     // fields
Pawn redpawn[4], bluepawn[4], yellowpawn[4], greenpawn[4];     // pawns

void dice(int n) 
{
    square.setFillColor(sf::Color::White);     // dice
    square.setSize(sf::Vector2f(100, 100));
    square.setOutlineThickness(5);
    square.setOutlineColor(sf::Color::Black);
    square.setPosition(WIDTH/2-50,HEIGHT/2-50);
    shape1.setFillColor(sf::Color::Black);     // dots 
    shape2.setFillColor(sf::Color::Black);
    shape3.setFillColor(sf::Color::Black);
    shape4.setFillColor(sf::Color::Black);
    shape5.setFillColor(sf::Color::Black);
    shape6.setFillColor(sf::Color::Black);
    shape7.setFillColor(sf::Color::Black);
    shape1.setPosition(WIDTH / 2 - 8, HEIGHT / 2 - 8);
    shape2.setPosition(WIDTH / 2 - 32, HEIGHT / 2 - 8);
    shape3.setPosition(WIDTH / 2 + 16, HEIGHT / 2 - 8);
    shape4.setPosition(WIDTH / 2 - 32, HEIGHT / 2 - 32);
    shape5.setPosition(WIDTH / 2 - 32, HEIGHT / 2 + 16);
    shape6.setPosition(WIDTH / 2 + 16, HEIGHT / 2 - 32);
    shape7.setPosition(WIDTH / 2 + 16, HEIGHT / 2 + 16);
    if(n==1 || n==5 || n==3) window.draw(shape1);
    if(n==6) window.draw(shape2);
    if(n==6) window.draw(shape3);
    if(n==6 || n==5 || n==4) window.draw(shape4);
    if(n!=1) window.draw(shape5);
    if(n!=1) window.draw(shape6);
    if(n==6 || n==5 || n==4) window.draw(shape7);
}

void boardfield()
{
    for (int i = 0; i < 3; i++){
        b[i].field(WIDTH/2 - 155 - i*105, HEIGHT/2 - 50, 0, 0, 250);     // blue fields
        window.draw(b[i]);
    }
    for (int i = 0; i < 3; i++) {
        y[i].field(WIDTH/2 - 50, HEIGHT/2 - 155 - i*105, 250, 250, 0);     // yellow fields
        window.draw(y[i]);
    }
    for (int i = 0; i < 3; i++) {
        g[i].field(WIDTH/2 + 55 + i*105, HEIGHT/2 - 50, 0, 250, 0);     // green fields
        window.draw(g[i]);
    }
    for (int i = 0; i < 3; i++) {
        r[i].field(WIDTH/2 - 50, HEIGHT/2 + 55 + i*105, 250, 0, 0);     // red fields
        window.draw(r[i]);
    }
    for (int i  =0, j = 0, k = 0; i < 7; i++) {
        p[i].field(WIDTH/2 - 155 - j*105, HEIGHT/2 + 370 - k*105);     // left bottom clear fields
        window.draw(p[i]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        p[i+7].field(WIDTH/2 - 470 + k*105, HEIGHT/2 - 155 - j*105);     // left top clear fields
        window.draw(p[i+7]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        p[i + 14].field(WIDTH/2 + 55 + j*105, HEIGHT/2 - 470 + k*105);     // right top clear fields
        window.draw(p[i + 14]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        p[i+21].field(WIDTH/2 + 370 - k*105, HEIGHT/2 + 55 + j*105);     // right bottom clear fields
        window.draw(p[i+21]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    p[29].field(WIDTH/2 - 470, HEIGHT/2 - 50);
    window.draw(p[29]);
    p[30].field(WIDTH/2 - 50, HEIGHT/2 - 470 );  
    window.draw(p[30]);
    p[31].field(WIDTH/2 + 370, HEIGHT/2 - 50);   
    window.draw(p[31]);
    p[32].field(WIDTH/2 - 50, HEIGHT/2 + 370);
    window.draw(p[32]);
    f[0].field(WIDTH / 2 - 470, HEIGHT / 2 + 370);     // fileds for red pawns
    f[1].field(WIDTH / 2 - 470, HEIGHT / 2 + 265);
    f[2].field(WIDTH / 2 - 365, HEIGHT / 2 + 370);
    f[3].field(WIDTH / 2 - 365, HEIGHT / 2 + 265);
    window.draw(f[0]);
    window.draw(f[1]);
    window.draw(f[2]);
    window.draw(f[3]);
    f[4].field(WIDTH / 2 - 470, HEIGHT / 2 - 470);     // fileds for blue pawns
    f[5].field(WIDTH / 2 - 470, HEIGHT / 2 - 365);
    f[6].field(WIDTH / 2 - 365, HEIGHT / 2 - 470);
    f[7].field(WIDTH / 2 - 365, HEIGHT / 2 - 365);
    window.draw(f[4]);
    window.draw(f[5]);
    window.draw(f[6]);
    window.draw(f[7]);
    f[8].field(WIDTH / 2 + 370, HEIGHT / 2 - 470);     // fileds for yellow pawns
    f[9].field(WIDTH / 2 + 370, HEIGHT / 2 - 365);
    f[10].field(WIDTH / 2 + 265, HEIGHT / 2 - 470);
    f[11].field(WIDTH / 2 + 265, HEIGHT / 2 - 365);
    window.draw(f[8]);
    window.draw(f[9]);
    window.draw(f[10]);
    window.draw(f[11]);
    f[12].field(WIDTH / 2 + 370, HEIGHT / 2 + 370);     // fileds for green pawns
    f[13].field(WIDTH / 2 + 370, HEIGHT / 2 + 265);
    f[14].field(WIDTH / 2 + 265, HEIGHT / 2 + 370);
    f[15].field(WIDTH / 2 + 265, HEIGHT / 2 + 265);
    window.draw(f[12]);
    window.draw(f[13]);
    window.draw(f[14]);
    window.draw(f[15]);
    sf::CircleShape redarrow(30,3), bluearrow(30,3), yellowarrow(30,3), greenarrow(30,3);     // arrows
    redarrow.setPosition(WIDTH/2 - 135, HEIGHT/2 + 400);
    redarrow.setFillColor(sf::Color::Red);
    redarrow.setOutlineThickness(5);
    redarrow.setOutlineColor(sf::Color::Black);
    window.draw(redarrow);
    bluearrow.setRotation(90);
    bluearrow.setPosition(WIDTH/2 - 400, HEIGHT/2 - 135);
    bluearrow.setFillColor(sf::Color::Blue);
    bluearrow.setOutlineThickness(5);
    bluearrow.setOutlineColor(sf::Color::Black);
    window.draw(bluearrow);
    yellowarrow.setRotation(180);
    yellowarrow.setPosition(WIDTH/2 + 135, HEIGHT/2 - 400);
    yellowarrow.setFillColor(sf::Color::Yellow);
    yellowarrow.setOutlineThickness(5);
    yellowarrow.setOutlineColor(sf::Color::Black);
    window.draw(yellowarrow);
    greenarrow.setRotation(270);
    greenarrow.setPosition(WIDTH/2 + 400, HEIGHT/2 + 135);
    greenarrow.setFillColor(sf::Color::Green);
    greenarrow.setOutlineThickness(5);
    greenarrow.setOutlineColor(sf::Color::Black);
    window.draw(greenarrow);
}

void setup_pawns()
{
    redpawn[0].pawn(140, 855, sf::Color::Red);
    redpawn[1].pawn(245, 855, sf::Color::Red);
    redpawn[2].pawn(245, 750, sf::Color::Red);
    redpawn[3].pawn(140, 750, sf::Color::Red);
    window.draw(redpawn[0]);
    window.draw(redpawn[1]);
    window.draw(redpawn[2]);
    window.draw(redpawn[3]);
    bluepawn[0].pawn(140, 120, sf::Color::Blue);
    bluepawn[1].pawn(245, 120, sf::Color::Blue);
    bluepawn[2].pawn(245, 15, sf::Color::Blue);
    bluepawn[3].pawn(140, 15, sf::Color::Blue);
    window.draw(bluepawn[0]);
    window.draw(bluepawn[1]);
    window.draw(bluepawn[2]);
    window.draw(bluepawn[3]);
    yellowpawn[0].pawn(875, 120, sf::Color::Yellow);
    yellowpawn[1].pawn(980, 120, sf::Color::Yellow);
    yellowpawn[2].pawn(980, 15, sf::Color::Yellow);
    yellowpawn[3].pawn(875, 15, sf::Color::Yellow);
    window.draw(yellowpawn[0]);
    window.draw(yellowpawn[1]);
    window.draw(yellowpawn[2]);
    window.draw(yellowpawn[3]);
    greenpawn[0].pawn(875, 855, sf::Color::Green);
    greenpawn[1].pawn(980, 855, sf::Color::Green);
    greenpawn[2].pawn(875, 750, sf::Color::Green);
    greenpawn[3].pawn(980, 750, sf::Color::Green);
    window.draw(greenpawn[0]);
    window.draw(greenpawn[1]);
    window.draw(greenpawn[2]);
    window.draw(greenpawn[3]);
}

int main()
{
    font.loadFromFile("arial.ttf");
    font1.loadFromFile("RAVIE.ttf");
    sf::Text text("Ludo", font1);     // title
    text.setPosition(350, 100);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(150);
    sf::Text text1("press to start game", font);     // button
    text1.setPosition(160, 750);
    text1.setFillColor(sf::Color::Black);
    text1.setCharacterSize(20);
    sf::Text text2("START", font);
    text2.setPosition(170, 670);
    text2.setFillColor(sf::Color::Black);
    text2.setCharacterSize(50);
    button.setFillColor(sf::Color::Red);
    button.setSize(sf::Vector2f(200, 70));
    button.setOutlineThickness(5);
    button.setOutlineColor(sf::Color::Black);
    button.setPosition(150,670);
    sf::Text text3("Instruction:", font);     //instruction
    text3.setPosition(750, 640);
    text3.setFillColor(sf::Color::Red);
    text3.setCharacterSize(30);
    sf::Text text4("pressing the spacebar stops the draw", font);
    text4.setPosition(750, 700);
    text4.setFillColor(sf::Color::Black);
    text4.setCharacterSize(20);
    sf::Text text5("click on a pawn to move it", font);
    text5.setPosition(750, 750);
    text5.setFillColor(sf::Color::Black);
    text5.setCharacterSize(20);
    sf::CircleShape triangle(30, 3);     //pawn
    triangle.setPosition(475, 128);
    triangle.setFillColor(sf::Color::Red);
    shape8.setPosition(489,120);
    shape8.setFillColor(sf::Color::Red);
    int i = 1; 
    bool game = false,result = true;
    while (window.isOpen())     // main loop
    {
        while (window.pollEvent(event))     // event
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && position.x > 150 && position.x < 350 && position.y>670 && position.y < 740)
                game = true;
        }

        if (game == false)     // start screen
        {
            window.clear(sf::Color(200, 200, 100));
            window.draw(button);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.draw(text5);
            window.draw(text);
            window.draw(triangle);
            window.draw(shape8);
            window.draw(square);
            dice(i);
            if (i == 6) i = 0;
            i++;
            window.setFramerateLimit(3);
            window.display();
        }
        else     // game
        {
            window.clear(sf::Color(200, 200, 100));
            window.draw(square);
            dice(i);
            if (result == true) i++; 
            if (i == 6) i = 0;
            if (event.key.code == sf::Keyboard::Space)
                result = false;
            window.setFramerateLimit(100);
            boardfield();
            setup_pawns();
            window.display();
        }
    }
    return 0;
}
