﻿#include <SFML/Graphics.hpp>
#include "board&pawns.h"

#define WIDTH 1200     // window size
#define HEIGHT 950

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ludo", sf::Style::Titlebar | sf::Style::Close);     // window
sf::CircleShape shape1(8), shape2(8), shape3(8), shape4(8), shape5(8), shape6(8), shape7(8), shape8(16);     // circles
sf::RectangleShape square, button;     // rectangles
sf::Event event;     // key i mouse
sf::Font font, font1;     // fonts
board b1, b2, b3, b4, y2, y3, y4, y5, g1, g2, g3, g4, r1, r2, r3, r4;

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
    b1.field(WIDTH / 2 - 155, HEIGHT / 2 - 50, 0, 0, 250);      // blue fields
    b2.field(WIDTH / 2 - 260, HEIGHT / 2 - 50, 0, 0, 250);
    b3.field(WIDTH / 2 - 365, HEIGHT / 2 - 50, 0, 0, 250);
    b4.field(WIDTH / 2 - 470, HEIGHT / 2 - 50, 0, 0, 250);
    window.draw(b1);
    window.draw(b2);
    window.draw(b3);
    window.draw(b4);
    y5.field(WIDTH / 2 - 50, HEIGHT / 2 - 155, 250, 250, 0);     // yellow fields
    y2.field(WIDTH / 2 - 50, HEIGHT / 2 - 260, 250, 250, 0);
    y3.field(WIDTH / 2 - 50, HEIGHT / 2 - 365, 250, 250, 0);
    y4.field(WIDTH / 2 - 50, HEIGHT / 2 - 470, 250, 250, 0);
    window.draw(y5);
    window.draw(y2);
    window.draw(y3);
    window.draw(y4);
    g1.field(WIDTH / 2 + 55, HEIGHT / 2 - 50, 0, 250, 0);     // green fields
    g2.field(WIDTH / 2 + 160, HEIGHT / 2 - 50, 0, 250, 0);
    g3.field(WIDTH / 2 + 265, HEIGHT / 2 - 50, 0, 250, 0);
    g4.field(WIDTH / 2 + 370, HEIGHT / 2 - 50, 0, 250, 0);
    window.draw(g1);
    window.draw(g2);
    window.draw(g3);
    window.draw(g4);
    r1.field(WIDTH / 2 - 50, HEIGHT / 2 + 55, 250, 0, 0);     // red fields
    r2.field(WIDTH / 2 - 50, HEIGHT / 2 + 160, 250, 0, 0);
    r3.field(WIDTH / 2 - 50, HEIGHT / 2 + 265, 250, 0, 0);
    r4.field(WIDTH / 2 - 50, HEIGHT / 2 + 370, 250, 0, 0);
    window.draw(r1);
    window.draw(r2);
    window.draw(r3);
    window.draw(r4);
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
    bool game = false;
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
            if (i == 6) i = 0;
            i++;
            window.setFramerateLimit(100);
            boardfield();
            window.display();
        }
    }
    return 0;
}