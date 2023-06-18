#include <SFML/Graphics.hpp>
#include "board&pawns.h"
#include <Windows.h>
#include <random>

#define WIDTH 1200     // window size
#define HEIGHT 950

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ludo", sf::Style::Titlebar | sf::Style::Close);     // window
sf::RectangleShape square;     //dice
sf::Texture texture1, texture2;
sf::Sprite sprite1, sprite2;
sf::Event event;     // key and mouse

const int cordsX[35] = { 0,0,0,-105,-105,-105,0,0,105,105,105,0,0,0,105,105,0,0,0,105,105,105,0,0,-105,-105,-105,0,0,0,-105,0,0,0,0 };     // repositioning coordinates
const int cordsY[35] = { -105,-105,-105,0,0,0,-105,-105,0,0,0,-105,-105,-105,0,0,105,105,105,0,0,0,105,105,0,0,0,105,105,105,0,-105,-105,-105,-105 };
const int tabx[16] = { 140,245,245,140,140,245,245,140,875,980,980,875,875,980,980,875 };
const int taby[16] = { 855,855,750,750,120,120,15 ,15 ,120,120,15 ,15 ,855,855,750,750 };     // starting coordinates
int i = 1, n = 0, player = 0, counter = 1, random = 0, tab[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
bool game = false, result = true;

int main()
{
    void dice(int n, sf::CircleShape shape[]);
    void display_Pawns_and_Boards(Board fields[], sf::CircleShape arrow[], Pawn pawns[], bool light = false);
    void players(Board fields[], sf::CircleShape arrow[], Pawn pawns[], sf::CircleShape shape[]);

    Pawn pawns[16];     // pawns
    for (int i = 0; i < 4; i++) {
        pawns[i] = Pawn(tabx[i], taby[i], sf::Color::Red);
        pawns[i + 4] = Pawn(tabx[i + 4], taby[i + 4], sf::Color::Blue);
        pawns[i + 8] = Pawn(tabx[i + 8], taby[i + 8], sf::Color::Yellow);
        pawns[i + 12] = Pawn(tabx[i + 12], taby[i + 12], sf::Color::Green);
    }

    Board fields[60];     // fields: 0-11 color, 12-27 base, 28-31 netural, 32-59 empty 
    for (int i = 0; i < 3; i++) {
        fields[i] = Board(WIDTH / 2 - 155 - i * 105, HEIGHT / 2 - 50, sf::Color::Blue);     // blue fields
        fields[i + 3] = Board(WIDTH / 2 - 50, HEIGHT / 2 - 155 - i * 105, sf::Color::Yellow);     // yellow fields
        fields[i + 6] = Board(WIDTH / 2 + 55 + i * 105, HEIGHT / 2 - 50, sf::Color::Green);     // green fields
        fields[i + 9] = Board(WIDTH / 2 - 50, HEIGHT / 2 + 55 + i * 105, sf::Color::Red);     // red fields
    }
    fields[12] = Board(WIDTH / 2 - 470, HEIGHT / 2 + 370);     // fields for red pawns
    fields[13] = Board(WIDTH / 2 - 470, HEIGHT / 2 + 265);
    fields[14] = Board(WIDTH / 2 - 365, HEIGHT / 2 + 370);
    fields[15] = Board(WIDTH / 2 - 365, HEIGHT / 2 + 265);
    fields[16] = Board(WIDTH / 2 - 470, HEIGHT / 2 - 470);     // fields for blue pawns
    fields[17] = Board(WIDTH / 2 - 470, HEIGHT / 2 - 365);
    fields[18] = Board(WIDTH / 2 - 365, HEIGHT / 2 - 470);
    fields[19] = Board(WIDTH / 2 - 365, HEIGHT / 2 - 365);
    fields[20] = Board(WIDTH / 2 + 370, HEIGHT / 2 - 470);     // fields for yellow pawns
    fields[21] = Board(WIDTH / 2 + 370, HEIGHT / 2 - 365);
    fields[22] = Board(WIDTH / 2 + 265, HEIGHT / 2 - 470);
    fields[23] = Board(WIDTH / 2 + 265, HEIGHT / 2 - 365);
    fields[24] = Board(WIDTH / 2 + 370, HEIGHT / 2 + 370);     // fields for green pawns
    fields[25] = Board(WIDTH / 2 + 370, HEIGHT / 2 + 265);
    fields[26] = Board(WIDTH / 2 + 265, HEIGHT / 2 + 370);
    fields[27] = Board(WIDTH / 2 + 265, HEIGHT / 2 + 265);
    fields[28] = Board(WIDTH / 2 - 155, HEIGHT / 2 + 370, 160, 160, 160);     // neutral fields
    fields[29] = Board(WIDTH / 2 - 470, HEIGHT / 2 - 155, 160, 160, 160);
    fields[30] = Board(WIDTH / 2 + 55, HEIGHT / 2 - 470, 160, 160, 160);
    fields[31] = Board(WIDTH / 2 + 370, HEIGHT / 2 + 55, 160, 160, 160);
    for (int i = 0, j = 0, k = 0; i < 6; i++) {
        fields[i + 32] = Board(WIDTH / 2 - 155 - j * 105, HEIGHT / 2 + 265 - k * 105);     // left bottom clear fields
        fields[i + 38] = Board(WIDTH / 2 - 365 + k * 105, HEIGHT / 2 - 155 - j * 105);     // left top clear fields
        fields[i + 44] = Board(WIDTH / 2 + 55 + j * 105, HEIGHT / 2 - 365 + k * 105);     // right top clear fields
        fields[i + 50] = Board(WIDTH / 2 + 265 - k * 105, HEIGHT / 2 + 55 + j * 105);     // right bottom clear fields
        if (i >= 2) j++;
        if (i < 2) k++;
    }
    fields[56] = Board(WIDTH / 2 - 470, HEIGHT / 2 - 50);
    fields[57] = Board(WIDTH / 2 - 50, HEIGHT / 2 - 470);
    fields[58] = Board(WIDTH / 2 + 370, HEIGHT / 2 - 50);
    fields[59] = Board(WIDTH / 2 - 50, HEIGHT / 2 + 370);

    sf::CircleShape arrow[4] = { sf::CircleShape(30, 3), sf::CircleShape(30, 3), sf::CircleShape(30, 3), sf::CircleShape(30, 3) };      // arrows
    for (int i = 0; i < 4; i++) {
        arrow[i].setOutlineThickness(5);
        arrow[i].setOutlineColor(sf::Color::Black);
        arrow[i].setRotation(i * 90);
    }
    arrow[0].setPosition(WIDTH / 2 - 135, HEIGHT / 2 + 400);
    arrow[0].setFillColor(sf::Color::Red);
    arrow[1].setPosition(WIDTH / 2 - 400, HEIGHT / 2 - 135);
    arrow[1].setFillColor(sf::Color::Blue);
    arrow[2].setPosition(WIDTH / 2 + 135, HEIGHT / 2 - 400);
    arrow[2].setFillColor(sf::Color::Yellow);
    arrow[3].setPosition(WIDTH / 2 + 400, HEIGHT / 2 + 135);
    arrow[3].setFillColor(sf::Color::Green);

    sf::CircleShape shape[7];     // circles
    for (int i = 0; i < 7; ++i) {
        shape[i] = sf::CircleShape(8);
        shape[i].setFillColor(sf::Color::Black);
    }
    shape[0].setPosition(WIDTH / 2 - 8, HEIGHT / 2 - 8);
    shape[1].setPosition(WIDTH / 2 - 32, HEIGHT / 2 - 8);
    shape[2].setPosition(WIDTH / 2 + 16, HEIGHT / 2 - 8);
    shape[3].setPosition(WIDTH / 2 - 32, HEIGHT / 2 - 32);
    shape[4].setPosition(WIDTH / 2 - 32, HEIGHT / 2 + 16);
    shape[5].setPosition(WIDTH / 2 + 16, HEIGHT / 2 - 32);
    shape[6].setPosition(WIDTH / 2 + 16, HEIGHT / 2 + 16);

    sf::RectangleShape button, neutral;     // rectangles
    neutral.setFillColor(sf::Color(160, 160, 160));
    neutral.setSize(sf::Vector2f(30, 30));
    neutral.setOutlineThickness(5);
    neutral.setOutlineColor(sf::Color::Black);
    neutral.setPosition(755, 750);
    button.setFillColor(sf::Color::Red);
    button.setSize(sf::Vector2f(200, 70));
    button.setOutlineThickness(5);
    button.setOutlineColor(sf::Color::Black);
    button.setPosition(150, 670);

    sf::Font font, font1;     // fonts
    font.loadFromFile("fonts/arial.ttf");
    font1.loadFromFile("fonts/RAVIE.ttf");

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

    sf::Text text3("Instruction:", font);     //instruction
    text3.setPosition(750, 640);
    text3.setFillColor(sf::Color::Red);
    text3.setCharacterSize(30);

    sf::Text text4("pressing the spacebar stops the draw", font);
    text4.setPosition(750, 700);
    text4.setFillColor(sf::Color::Black);
    text4.setCharacterSize(20);

    sf::Text text5("click on a pawn to move it", font);
    text5.setPosition(750, 800);
    text5.setFillColor(sf::Color::Black);
    text5.setCharacterSize(20);

    sf::CircleShape triangle(30, 3);     //pawn
    triangle.setPosition(475, 128);
    triangle.setFillColor(sf::Color::Red);

    sf::CircleShape shape8(16);
    shape8.setPosition(489, 120);
    shape8.setFillColor(sf::Color::Red);

    sf::Text text6("grey is a neutral field", font);
    text6.setPosition(800, 750);
    text6.setFillColor(sf::Color::Black);
    text6.setCharacterSize(20);

    texture1.loadFromFile("img/Cup.png");
    sprite1.setTexture(texture1);
    sprite1.setPosition(WIDTH / 2 - 60, HEIGHT / 2 - 100);
    texture2.loadFromFile("img/X.png");
    sprite2.setTexture(texture2);

    while (window.isOpen())     // main loop
    {
        while (window.pollEvent(event))     // event
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            sf::Vector2i position = sf::Mouse::getPosition(window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && position.x > 150 && position.x < 350 && position.y>670 && position.y < 740) {
                game = true;
                window.clear(sf::Color(200, 200, 100));
            }
        }

        if (game == false)     // start screen
        {
            window.clear(sf::Color(200, 200, 100));
            window.setFramerateLimit(3);
            window.draw(button);
            window.draw(text1);
            window.draw(text2);
            window.draw(text3);
            window.draw(text4);
            window.draw(text5);
            window.draw(text6);
            window.draw(text);
            window.draw(triangle);
            window.draw(shape8);
            window.draw(neutral);
            dice(i, shape);
            i++;
            if (i == 7) i = 1;
            window.display();
        }
        else     // game        
        {
            if (tab[player * 4] == 2 && tab[player * 4 + 1] == 2 && tab[player * 4 + 2] == 2 && tab[player * 4 + 3] == 2) player++;
            else {
                window.setFramerateLimit(100);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && player == 0)
                    result = false;
                if (player != 0 && counter == 1) random = rand() % 50 + 100;
                if (player != 0) counter++;
                if (counter == random) {
                    result = false;
                    counter = 1;
                }
                if (result == false)
                {
                    Sleep(250);
                    players(fields, arrow, pawns, shape);
                    result = true;
                }
                else i++;
                if (i == 7) i = 1;
                window.clear(sf::Color(200, 200, 100));
                display_Pawns_and_Boards(fields, arrow, pawns);
                dice(i, shape);
                window.display();
                int k = 0;
                for (int j = 0; j < 4; j++)
                    if (tab[j * 4] == 2 && tab[j * 4 + 1] == 2 && tab[j * 4 + 2] == 2 && tab[j * 4 + 3] == 2) k++;
                if ((tab[0] == 2 && tab[1] == 2 && tab[2] == 2 && tab[3] == 2) || k == 3) game = false;
            }
        }
    }
    return 0;
}

void dice(int n, sf::CircleShape shape[])
{
    square.setFillColor(sf::Color::White);     // dice 
    square.setSize(sf::Vector2f(100, 100));
    square.setOutlineThickness(5);
    if (player == 0) square.setOutlineColor(sf::Color::Red);
    else if (player == 1) square.setOutlineColor(sf::Color::Blue);
    else if (player == 2) square.setOutlineColor(sf::Color::Yellow);
    else if (player == 3) square.setOutlineColor(sf::Color::Green);
    if (game == false) square.setOutlineColor(sf::Color::Black);
    square.setPosition(WIDTH / 2 - 50, HEIGHT / 2 - 50);
    window.draw(square);
    if (n == 1 || n == 5 || n == 3) window.draw(shape[0]);
    if (n == 6) window.draw(shape[1]);
    if (n == 6) window.draw(shape[2]);
    if (n == 6 || n == 5 || n == 4) window.draw(shape[3]);
    if (n != 1) window.draw(shape[4]);
    if (n != 1) window.draw(shape[5]);
    if (n == 6 || n == 5 || n == 4) window.draw(shape[6]);
}

void display_Pawns_and_Boards(Board fields[], sf::CircleShape arrow[], Pawn pawns[], bool light = false)
{
    for (int i = 0; i < 60; i++) 
        window.draw(fields[i]);
    for (int i = 0; i < 4; i++)
        window.draw(arrow[i]);

    int h = 0, x = 0;
    for (int j = 0; j < 16; j++) {
        h = (player + 1) * 4 + j;
        if (h >= 16) h -= 16;
        if (light && h < 4 && tab[h] == 1) pawns[h].pawn(true);
        else if (light && h < 4 && x == 0 && i == 6 && tab[h] == 0) {
            pawns[h].pawn(true);
            x = 1;
        }
        else pawns[h].pawn();
        window.draw(pawns[h]);
    }
}

void players(Board fields[], sf::CircleShape arrow[], Pawn pawns[], sf::CircleShape shape[])
{
    int pawnOnBoard = 0, h = 20, pawnOnBase = 0, x = 0;
    bool next = false;
    for (int j = 0; j < 4; j++) {    // number of pawns on board and base
        if (35 - i < pawns[player * 4 + j].getIdx() && tab[player * 4 + j] != 2) tab[player * 4 + j] = 3;
        if (tab[player * 4 + j] == 1) pawnOnBoard += 1;
        if (tab[player * 4 + j] == 0) pawnOnBase += 1;
    }
    if (pawnOnBoard > 0 && player == 0) {
        window.clear(sf::Color(200, 200, 100));
        dice(i, shape);
        if (pawnOnBoard == 1 && i != 6) display_Pawns_and_Boards(fields, arrow, pawns);
        else display_Pawns_and_Boards(fields, arrow, pawns, true);
        window.display();
        while (pawnOnBoard > 0) {
            while (window.pollEvent(event))     // event
            {
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            if ((pawnOnBoard == 1 && i != 6) || (pawnOnBase == 0 && i == 6)) {
                for (int j = 0; j < 4; j++)
                    if (tab[j] == 1) {
                        for (int a = 0; a < i; a++) {
                            Sleep(250);
                            window.clear(sf::Color(200, 200, 100));
                            dice(i, shape);
                            pawns[j].setX(pawns[j].getX() + cordsX[pawns[j].getIdx() + a]); 
                            pawns[j].setY(pawns[j].getY() + cordsY[pawns[j].getIdx() + a]);     // pawn moves 
                            display_Pawns_and_Boards(fields, arrow, pawns);
                            window.display();
                        }
                        for (int k = 0; k < 12; k++)
                            if (pawns[j].getX() == pawns[k + 4].getX() && pawns[j].getY() == pawns[k + 4].getY()) {     // pawn on another pawn
                                if ((pawns[j].getX() == WIDTH / 2 - 145 && pawns[j].getY() == HEIGHT / 2 + 380) || (pawns[j].getX() == WIDTH / 2 - 460 && pawns[j].getY() == HEIGHT / 2 - 145)
                                    || (pawns[j].getX() == WIDTH / 2 + 65 && pawns[j].getY() == HEIGHT / 2 - 460) || (pawns[j].getX() == WIDTH / 2 + 380 && pawns[j].getY() == HEIGHT / 2 + 65)) break;
                                sprite2.setPosition(pawns[j].getX(), pawns[j].getY());
                                window.clear(sf::Color(200, 200, 100));
                                dice(i, shape);
                                display_Pawns_and_Boards(fields, arrow, pawns);
                                window.draw(sprite2);
                                window.display();
                                Sleep(1000);
                                pawns[k + 4].setX(pawns[k + 4].getX() + tabx[k + 4]);
                                pawns[k + 4].setY(pawns[k + 4].getY() + taby[k + 4]);
                                pawns[k + 4].setIdx(0);
                                tab[k + 4] = 0;
                                x = 1;
                            } 
                        if (x == 0 && i != 6) next = true;
                        pawns[j].setIdx(pawns[j].getIdx() + i);
                        pawnOnBoard = 0;
                        break;
                    }
            }
            else if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     // select a pawn
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                for (int j = 0; j < 4; j++) {
                    if (i == 6 && position.x > WIDTH / 2 - 470 && position.x < WIDTH / 2 - 260 && position.y>HEIGHT / 2 + 265 && position.y < HEIGHT / 2 + 475 && pawnOnBase > 0)
                    {
                        for (int j = 0; j < 4; j++)
                            if (tab[j] == 0) {
                                pawns[j].setX(WIDTH / 2 - 145);     // pawn goes on the board  
                                pawns[j].setY(HEIGHT / 2 + 380);
                                tab[j] = 1;
                                break;
                            }
                        window.clear(sf::Color(200, 200, 100));
                        dice(i, shape);
                        display_Pawns_and_Boards(fields, arrow, pawns);
                        window.display();
                        Sleep(1000);
                        pawnOnBoard = 0;
                        break;
                    }
                    else if ((pawns[j].getX() + 40 - position.x) * (pawns[j].getX() + 40 - position.x) + (pawns[j].getY() + 40 - position.y) * (pawns[j].getY() + 40 - position.y) <= 1600 && tab[j] == 1)
                    {
                        for (int a = 0; a < i; a++) {
                            Sleep(250);
                            window.clear(sf::Color(200, 200, 100));
                            dice(i, shape);
                            pawns[j].setX(pawns[j].getX() + cordsX[pawns[j].getIdx() + a]);
                            pawns[j].setY(pawns[j].getY() + cordsY[pawns[j].getIdx() + a]);     // pawn moves 
                            display_Pawns_and_Boards(fields, arrow, pawns);
                            window.display();
                        }
                        for (int k = 0; k < 12; k++)
                            if (pawns[j].getX() == pawns[k + 4].getX() && pawns[j].getY() == pawns[k + 4].getY()) {     // pawn on another pawn
                                if ((pawns[j].getX() == WIDTH / 2 - 145 && pawns[j].getY() == HEIGHT / 2 + 380) || (pawns[j].getX() == WIDTH / 2 - 460 && pawns[j].getY() == HEIGHT / 2 - 145)
                                    || (pawns[j].getX() == WIDTH / 2 + 65 && pawns[j].getY() == HEIGHT / 2 - 460) || (pawns[j].getX() == WIDTH / 2 + 380 && pawns[j].getY() == HEIGHT / 2 + 65)) break;
                                sprite2.setPosition(pawns[j].getX(), pawns[j].getY());
                                window.clear(sf::Color(200, 200, 100));
                                dice(i, shape);
                                display_Pawns_and_Boards(fields, arrow, pawns);
                                window.draw(sprite2);
                                window.display();
                                Sleep(1000);
                                pawns[k + 4].setX(tabx[k + 4]);
                                pawns[k + 4].setY(taby[k + 4]);
                                pawns[k + 4].setIdx(0);
                                tab[k + 4] = 0;
                                x = 1;
                            }
                        if (x == 0 && i != 6) next = true;
                        pawns[j].setIdx(pawns[j].getIdx() + i);
                        pawnOnBoard = 0;
                        break;
                    }
                }
            }
        }
    }
    else if (pawnOnBoard > 0 && player != 0) {
        for (int k = 0; k < 4; k++)
            if (tab[player * 4 + k] == 1)
                for (int l = 0; l < i; l++) {     // checking possibility to beat
                    if (player == 1) {
                        pawns[k + 4].setX(pawns[k + 4].getX() - cordsY[pawns[k + 4].getIdx() + l]);
                        pawns[k + 4].setY(pawns[k + 4].getY() + cordsX[pawns[k + 4].getIdx() + l]);
                    }
                    else if (player == 2) {
                        pawns[k + 8].setX(pawns[k + 8].getX() - cordsX[pawns[k + 8].getIdx() + l]);
                        pawns[k + 8].setY(pawns[k + 8].getY() - cordsY[pawns[k + 8].getIdx() + l]);
                    }
                    else if (player == 3) {
                        pawns[k + 12].setX(pawns[k + 12].getX() + cordsY[pawns[k + 12].getIdx() + l]);
                        pawns[k + 12].setY(pawns[k + 12].getY() - cordsX[pawns[k + 12].getIdx() + l]);
                    }
                    if (l == i - 1) pawns[player * 4 + k].setIdx(pawns[player * 4 + k].getIdx() + i - 1);
                }
        for (int k = 0; k < 4; k++)
            for (int j = 0; j < 16; j++)
                if (j != player * 4 && j != player * 4 + 1 && j != player * 4 + 2 && j != player * 4 + 3)
                    if (pawns[player * 4 + k].getX() == pawns[j].getX() && pawns[player * 4 + k].getY() == pawns[j].getY()) {
                        h = player * 4 + k;
                        j = 20;
                        k = 20;
                    }
        for (int k = 0; k < 4; k++)
            if (tab[player * 4 + k] == 1)
                for (int l = 0; l < i; l++) {
                    if (player == 1) {
                        pawns[k + 4].setX(pawns[k + 4].getX() + cordsY[pawns[k + 4].getIdx() - l]);
                        pawns[k + 4].setY(pawns[k + 4].getY() - cordsX[pawns[k + 4].getIdx() - l]);
                    }
                    else if (player == 2) {
                        pawns[k + 8].setX(pawns[k + 8].getX() + cordsX[pawns[k + 8].getIdx() - l]);
                        pawns[k + 8].setY(pawns[k + 8].getY() + cordsY[pawns[k + 8].getIdx() - l]);
                    }
                    else if (player == 3) {
                        pawns[k + 12].setX(pawns[k + 12].getX() - cordsY[pawns[k + 12].getIdx() - l]);
                        pawns[k + 12].setY(pawns[k + 12].getY() + cordsX[pawns[k + 12].getIdx() - l]);
                    }
                    if (l == i - 1) pawns[player * 4 + k].setIdx(pawns[player * 4 + k].getIdx() - i + 1);
                }
        if (h != 20) {     // beat is possible
            for (int a = 0; a < i; a++) {
                Sleep(250);
                window.clear(sf::Color(200, 200, 100));
                dice(i, shape);
                if (player == 1) {
                    pawns[h].setX(pawns[h].getX() - cordsY[pawns[h].getIdx() + a]);
                    pawns[h].setY(pawns[h].getY() + cordsX[pawns[h].getIdx() + a]);
                }
                else if (player == 2) {
                    pawns[h].setX(pawns[h].getX() - cordsX[pawns[h].getIdx() + a]);
                    pawns[h].setY(pawns[h].getY() - cordsY[pawns[h].getIdx() + a]);
                }
                else if (player == 3) {
                    pawns[h].setX(pawns[h].getX() + cordsY[pawns[h].getIdx() + a]);
                    pawns[h].setY(pawns[h].getY() - cordsX[pawns[h].getIdx() + a]);
                }
                display_Pawns_and_Boards(fields, arrow, pawns);
                window.display();
            }
            for (int j = 0; j < 16; j++)     // knock down pawns
                if (j != player * 4 && j != player * 4 + 1 && j != player * 4 + 2 && j != player * 4 + 3)
                    if (pawns[h].getX() == pawns[j].getX() && pawns[h].getY() == pawns[j].getY()) {
                        if ((pawns[j].getX() == WIDTH / 2 - 145 && pawns[j].getY() == HEIGHT / 2 + 380) || (pawns[j].getX() == WIDTH / 2 - 460 && pawns[j].getY() == HEIGHT / 2 - 145)
                            || (pawns[j].getX() == WIDTH / 2 + 65 && pawns[j].getY() == HEIGHT / 2 - 460) || (pawns[j].getX() == WIDTH / 2 + 380 && pawns[j].getY() == HEIGHT / 2 + 65)) break;
                        sprite2.setPosition(pawns[h].getX(), pawns[h].getY());
                        window.clear(sf::Color(200, 200, 100));
                        dice(i, shape);
                        display_Pawns_and_Boards(fields, arrow, pawns);
                        window.draw(sprite2);
                        window.display();
                        Sleep(1000);
                        pawns[j].setX(tabx[j]);
                        pawns[j].setY(taby[j]);
                        pawns[j].setIdx(0);
                        tab[j] = 0;
                    }
            if (((pawns[h].getX() == WIDTH / 2 - 145 && pawns[h].getY() == HEIGHT / 2 + 380) || (pawns[h].getX() == WIDTH / 2 - 460 && pawns[h].getY() == HEIGHT / 2 - 145)
                || (pawns[h].getX() == WIDTH / 2 + 65 && pawns[h].getY() == HEIGHT / 2 - 460) || (pawns[h].getX() == WIDTH / 2 + 380 && pawns[h].getY() == HEIGHT / 2 + 65)) && i != 6)
                next = true;
            pawns[h].setIdx(pawns[h].getIdx() + i);
        }
        else {     // beat is not possible
            if (i == 6 && pawnOnBase > 0) {
                for (int j = 0; j < 4; j++)
                    if (tab[player * 4 + j] == 0) {
                        if (player == 1) {
                            pawns[j + 4].setX(WIDTH / 2 - 460);
                            pawns[j + 4].setY(HEIGHT / 2 - 145);
                        }
                        else if (player == 2) {
                            pawns[j + 8].setX(WIDTH / 2 + 65);
                            pawns[j + 8].setY(HEIGHT / 2 - 460);
                        }
                        else if (player == 3) {
                            pawns[j + 12].setX(WIDTH / 2 + 380);
                            pawns[j + 12].setY(HEIGHT / 2 + 65);
                        }
                        tab[player * 4 + j] = 1;
                        break;
                    }
                window.clear(sf::Color(200, 200, 100));
                dice(i, shape);
                display_Pawns_and_Boards(fields, arrow, pawns);
                window.display();
                Sleep(1000);
            }
            else if (pawnOnBoard > 0) {
                for (int j = 0; j < 4; j++)
                    if (tab[player * 4 + j] == 1) {
                        h = player * 4 + j;
                        break;
                    }
                for (int j = 0; j < 4; j++)
                    if (35 - i == pawns[player * 4 + j].getIdx()) h = player * 4 + j;
                for (int a = 0; a < i; a++) {
                    window.clear(sf::Color(200, 200, 100));
                    dice(i, shape);
                    if (player == 1) {
                        pawns[h].setX(pawns[h].getX() - cordsY[pawns[h].getIdx() + a]);
                        pawns[h].setY(pawns[h].getY() + cordsX[pawns[h].getIdx() + a]);
                    }
                    else if (player == 2) {
                        pawns[h].setX(pawns[h].getX() - cordsX[pawns[h].getIdx() + a]);
                        pawns[h].setY(pawns[h].getY() - cordsY[pawns[h].getIdx() + a]);
                    }
                    else if (player == 3) {
                        pawns[h].setX(pawns[h].getX() + cordsY[pawns[h].getIdx() + a]);
                        pawns[h].setY(pawns[h].getY() - cordsX[pawns[h].getIdx() + a]);
                    }
                    display_Pawns_and_Boards(fields, arrow, pawns);
                    window.display();
                    Sleep(250);
                }
                pawns[h].setIdx(pawns[h].getIdx() + i);
                if (i != 6) next = true;
            }
        }
    }
    else {     // 0 pawns on the board
        if (i == 6 && pawnOnBase > 0) {
            for (int j = 0; j < 4; j++)
                if (tab[player * 4 + j] == 0) {
                    if (player == 0) {
                        pawns[j].setX(WIDTH / 2 - 145);
                        pawns[j].setY(HEIGHT / 2 + 380);
                    }
                    else if (player == 1) {
                        pawns[player * 4 + j].setX(WIDTH / 2 - 460);
                        pawns[player * 4 + j].setY(HEIGHT / 2 - 145);
                    }
                    else if (player == 2) {
                        pawns[player * 4 + j].setX(WIDTH / 2 + 65);
                        pawns[player * 4 + j].setY(HEIGHT / 2 - 460);
                    }
                    else if (player == 3) {
                        pawns[player * 4 + j].setX(WIDTH / 2 + 380);
                        pawns[player * 4 + j].setY(HEIGHT / 2 + 65);
                    }
                    tab[player * 4 + j] = 1;
                    break;
                }
            window.clear(sf::Color(200, 200, 100));
            dice(i, shape);
            display_Pawns_and_Boards(fields, arrow, pawns);
            window.display();
            Sleep(1000);
        }
        else {     // do nothing
            next = true;
            Sleep(1000);
        }
    }
    for (int j = 0; j < 4; j++)
        if (tab[player * 4 + j] == 3) tab[player * 4 + j] = 1;
    for (int j = 0; j < 4; j++)
        if (pawns[player * 4 + j].getX() == WIDTH / 2 - 40 && pawns[player * 4 + j].getY() == HEIGHT / 2 - 40) {     // pawn reaches the finish line
            window.clear(sf::Color(200, 200, 100));
            dice(i, shape);
            display_Pawns_and_Boards(fields, arrow, pawns);
            window.draw(sprite1);
            window.display();
            Sleep(1000);
            pawns[player * 4 + j].setY(1000);
            tab[player * 4 + j] = 2;
            next = false;
            break;
        }
    n++;
    if (n >= 3 || next == true) {     // max 3 throws
        n = 0;
        player++;
        if (player == 4) player = 0;
    }
}