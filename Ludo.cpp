#include <SFML/Graphics.hpp>
#include "board&pawns.h"
#include <Windows.h>
#include <random>

#define WIDTH 1200     // window size
#define HEIGHT 950

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Ludo", sf::Style::Titlebar | sf::Style::Close);     // window
sf::CircleShape shape1(8), shape2(8), shape3(8), shape4(8), shape5(8), shape6(8), shape7(8), shape8(16);     // circles
sf::RectangleShape square, button, neutral;     // rectangles
sf::Event event;     // key i mouse
sf::Font font, font1;     // fonts
Board b[3], y[3], g[3], r[3], p[32], f[16];     // fields 
Pawn pawns[16];     // pawns
const int cordsX[35] = {0,0,0,-105,-105,-105,0,0,105,105,105,0,0,0,105,105,0,0,0,105,105,105,0,0,-105,-105,-105,0,0,0,-105,0,0,0,0};     // repositioning coordinates
const int cordsY[35] = {-105,-105,-105,0,0,0,-105,-105,0,0,0,-105,-105,-105,0,0,105,105,105,0,0,0,105,105,0,0,0,105,105,105,0,-105,-105,-105,-105};
const int tabx[16] = { 140,245,245,140,140,245,245,140,875,980,980,875,875,980,980,875 };
const int taby[16] = { 855,855,750,750,120,120,15 ,15 ,120,120,15 ,15 ,855,855,750,750 };     // starting coordinates
int i = 1, n = 0, player = 0, counter = 1, random = 0, tab[16] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
bool game = false, result = true;

void dice(int n) 
{
    square.setFillColor(sf::Color::White);     // dice 
    square.setSize(sf::Vector2f(100, 100));
    square.setOutlineThickness(5);
    if (player == 0) square.setOutlineColor(sf::Color::Red);
    else if (player == 1) square.setOutlineColor(sf::Color::Blue);
    else if (player == 2) square.setOutlineColor(sf::Color::Yellow);
    else if (player == 3) square.setOutlineColor(sf::Color::Green);
    if (game == false) square.setOutlineColor(sf::Color::Black); 
    square.setPosition(WIDTH/2-50,HEIGHT/2-50);
    window.draw(square);
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
    
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        if (i==0) p[i].field(WIDTH/2 - 155, HEIGHT/2 + 370, 160, 160, 160);
        else p[i].field(WIDTH/2 - 155 - j*105, HEIGHT/2 + 370 - k*105);     // left bottom clear fields
        window.draw(p[i]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        if (i==0) p[i+7].field(WIDTH/2 - 470, HEIGHT/2 - 155, 160, 160, 160);
        else p[i+7].field(WIDTH/2 - 470 + k*105, HEIGHT/2 - 155 - j*105);     // left top clear fields
        window.draw(p[i+7]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        if (i==0) p[i+14].field(WIDTH/2 + 55, HEIGHT/2 - 470, 160, 160, 160);
        else p[i + 14].field(WIDTH/2 + 55 + j*105, HEIGHT/2 - 470 + k*105);     // right top clear fields
        window.draw(p[i + 14]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    for (int i = 0, j = 0, k = 0; i < 7; i++) {
        if (i==0) p[i+21].field(WIDTH/2 + 370, HEIGHT/2 + 55, 160, 160, 160);
        else p[i+21].field(WIDTH/2 + 370 - k*105, HEIGHT/2 + 55 + j*105);     // right bottom clear fields
        window.draw(p[i+21]);
        if (i >= 3) j++;
        if (i < 3) k++;
    }
    p[28].field(WIDTH/2 - 470, HEIGHT/2 - 50);
    window.draw(p[28]);
    p[29].field(WIDTH/2 - 50, HEIGHT/2 - 470 );  
    window.draw(p[29]);
    p[30].field(WIDTH/2 + 370, HEIGHT/2 - 50);   
    window.draw(p[30]);
    p[31].field(WIDTH/2 - 50, HEIGHT/2 + 370);
    window.draw(p[31]);
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

void displayPawns()
{
    for (int i = 0; i < 16; i++) {
        pawns[i].pawn();
        window.draw(pawns[i]);
    }
}

void gamer()
{
    int pawnOnBoard = 0;
    for (int j = 0; j < 4; j++)     // number of pawns on board
        if (tab[j] == 1) pawnOnBoard += 1;
    if (pawnOnBoard > 0) {
        while (pawnOnBoard > 0) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))     // select a pawn
            {
                sf::Vector2i position = sf::Mouse::getPosition(window);
                for (int j = 0; j < 4; j++) {
                    if (i == 6 && position.x > WIDTH / 2 - 470 && position.x < WIDTH / 2 - 260 && position.y>HEIGHT / 2 + 265 && position.y < HEIGHT / 2 + 475)
                    {
                        for (int j = 0; j < 4; j++)
                            if (tab[j] == 0) {
                                pawns[j].X = WIDTH / 2 - 145;     // pawn goes on the board  
                                pawns[j].Y = HEIGHT / 2 + 380;
                                tab[j] = 1;
                                break;
                            }
                        window.clear(sf::Color(200, 200, 100));
                        dice(i);
                        boardfield();
                        displayPawns();
                        window.display();
                        Sleep(1000);
                        pawnOnBoard = 0;
                        break;
                    }
                    else if ((pawns[j].X + 40 - position.x) * (pawns[j].X + 40 - position.x) + (pawns[j].Y + 40 - position.y) * (pawns[j].Y + 40 - position.y) <= 1600)
                    {
                        for (int a = 0; a < i; a++) {
                            window.clear(sf::Color(200, 200, 100));
                            dice(i);
                            boardfield();
                            pawns[j].X += cordsX[pawns[j].index + a];
                            pawns[j].Y += cordsY[pawns[j].index + a];     // pawn moves 
                            displayPawns();
                            window.display();
                            Sleep(250);
                        }
                        for (int i = 0, x = 0; i < 12; i++)
                            if (pawns[j].X == pawns[i + 4].X && pawns[j].Y == pawns[i + 4].Y)     // pawn on another pawn 
                                if((pawns[j].X != WIDTH/2 - 145 && pawns[j].Y != HEIGHT/2 + 380) || (pawns[j].X != WIDTH/2 - 460 && pawns[j].Y != HEIGHT/2 - 145) 
                                    || (pawns[j].X != WIDTH/2 + 65 && pawns[j].Y != HEIGHT/2 - 460) || (pawns[j].X != WIDTH/2 + 380 && pawns[j].Y != HEIGHT/2 + 65)){ 
                                    pawns[i + 4].X = tabx[i + 4];
                                    pawns[i + 4].Y = taby[i + 4];
                                    pawns[i + 4].index = 0;
                                    tab[i + 4] = 0;
                                    if(x == 0) player--;
                                    x = 1;
                                    window.clear(sf::Color(200, 200, 100));
                                    dice(i);
                                    boardfield();
                                    displayPawns();
                                    window.display();
                                }
                        player++;
                        pawns[j].index += i;
                        pawnOnBoard = 0;
                        break;
                    }
                }
            }
        }
    }
    else {
        if (i == 6) {     // pawn goes on the board
            for (int j = 0; j < 4; j++)
                if (tab[j] == 0) {
                    pawns[j].X = WIDTH / 2 - 145;
                    pawns[j].Y = HEIGHT / 2 + 380;
                    tab[j] = 1;
                    break;
                }
            window.clear(sf::Color(200, 200, 100));
            dice(i);
            boardfield();
            displayPawns();
            window.display();
            Sleep(1000);
        }
        else {     // do nothing
            n = -1;
            player++;
            Sleep(1000);
        }
    }
    for (int j = 0; j < 4; j++)
        if (pawns[j].X == WIDTH / 2 - 40 && pawns[j].Y == HEIGHT / 2 - 40) {     // pawn reaches the finish line
            pawns[j].Y = 1000;
            tab[j] = 2;
        }
    n++;
    if (n >= 3) {     // max 3 throws
        n = 0;
        player++;
    }
}

void robotGamers()
{
    int pawnOnBoard = 0, h = 20, pawnOnFinish = 0;
    for (int j = 0; j < 4; j++) {    // number of pawns on board and finish
        if (tab[player * 4 + j] == 1) pawnOnBoard += 1;
        if (tab[player * 4 + j] == 2) pawnOnFinish += 1;
    }
    if (pawnOnBoard > 0) {
        for (int k = 0; k < 4; k++)
            if (tab[player * 4 + k] == 1)
                for (int l = 0; l <= i; l++) {     // checking possibility to beat
                    if (player == 1) {
                        pawns[player * 4 + k].X -= cordsY[pawns[player * 4 + k].index + l];
                        pawns[player * 4 + k].Y += cordsX[pawns[player * 4 + k].index + l];
                    }
                    else if (player == 2) {
                        pawns[player * 4 + k].X -= cordsX[pawns[player * 4 + k].index + l];
                        pawns[player * 4 + k].Y -= cordsY[pawns[player * 4 + k].index + l];
                    }
                    else if (player == 3) {
                        pawns[player * 4 + k].X += cordsY[pawns[player * 4 + k].index + l];
                        pawns[player * 4 + k].Y -= cordsX[pawns[player * 4 + k].index + l];
                    }
                    if (l == i) pawns[player * 4 + k].index += i;
                }
        for (int k = 0; k < 4; k++)
            for (int j = 0; j < 16; j++)
                if (j != player * 4 && j != player * 4 + 1 && j != player * 4 + 2 && j != player * 4 + 3)
                    if (pawns[player * 4 + k].X == pawns[j].X && pawns[player * 4 + k].Y == pawns[j].Y) {
                        h = j;
                        j, k = 20; 
                    }
        for (int k = 0; k < 4; k++)
            if (tab[player * 4 + k] == 1)
                for (int l = 0; l <= i; l++) {
                    if (player == 1) {
                        pawns[player * 4 + k].X += cordsY[pawns[player * 4 + k].index - l];
                        pawns[player * 4 + k].Y -= cordsX[pawns[player * 4 + k].index - l];
                    }
                    else if (player == 2) {
                        pawns[player * 4 + k].X += cordsX[pawns[player * 4 + k].index - l];
                        pawns[player * 4 + k].Y += cordsY[pawns[player * 4 + k].index - l];
                    }
                    else if (player == 3) {
                        pawns[player * 4 + k].X -= cordsY[pawns[player * 4 + k].index - l];
                        pawns[player * 4 + k].Y += cordsX[pawns[player * 4 + k].index - l];
                    }
                    if (l == i) pawns[player * 4 + k].index -= i;
                }
        if (h != 20) {     // beat is possible
            for (int a = 0; a < i; a++) {
                window.clear(sf::Color(200, 200, 100));
                dice(i);
                boardfield();
                if (player == 1) {
                    pawns[h].X -= cordsY[pawns[h].index + a];
                    pawns[h].Y += cordsX[pawns[h].index + a];
                }
                else if (player == 2) {
                    pawns[h].X -= cordsX[pawns[h].index + a];
                    pawns[h].Y -= cordsY[pawns[h].index + a];
                }
                else if (player == 3) {
                    pawns[h].X += cordsY[pawns[h].index + a];
                    pawns[h].Y -= cordsX[pawns[h].index + a];
                }
                displayPawns();
                window.display();
                Sleep(250);
            }    
            for (int j = 0; j < 16; j++)     // knock down pawns 
                if (j != player * 4 && j != player * 4 + 1 && j != player * 4 + 2 && j != player * 4 + 3)
                    if (pawns[h].X == pawns[j].X && pawns[h].Y == pawns[j].Y) 
                        if ((pawns[j].X != WIDTH / 2 - 145 && pawns[j].Y != HEIGHT / 2 + 380) || (pawns[j].X != WIDTH / 2 - 460 && pawns[j].Y != HEIGHT / 2 - 145)
                            || (pawns[j].X != WIDTH / 2 + 65 && pawns[j].Y != HEIGHT / 2 - 460) || (pawns[j].X != WIDTH / 2 + 380 && pawns[j].Y != HEIGHT / 2 + 65)) {
                            pawns[j].X = tabx[j];
                            pawns[j].Y = taby[j];
                            pawns[j].index = 0;
                            tab[j] = 0;
                            window.clear(sf::Color(200, 200, 100));
                            dice(i);
                            boardfield();
                            displayPawns();
                            window.display();
                        }
            pawns[h].index += i;
        }
        else {     // beat is not possible
            if (i == 6 && pawnOnBoard + pawnOnFinish < 4) {
                for (int j = 0; j < 4; j++) 
                    if (tab[player * 4 + j] == 0) {
                        if (player == 1) {
                            pawns[player * 4 + j].X = WIDTH / 2 - 460;
                            pawns[player * 4 + j].Y = HEIGHT / 2 - 145;
                        }
                        else if (player == 2) {
                            pawns[player * 4 + j].X = WIDTH / 2 + 65;
                            pawns[player * 4 + j].Y = HEIGHT / 2 - 460;
                        }
                        else if (player == 3) {
                            pawns[player * 4 + j].X = WIDTH / 2 + 380;
                            pawns[player * 4 + j].Y = HEIGHT / 2 + 65;
                        }
                        tab[player * 4 + j] = 1;
                        break;
                    }
                window.clear(sf::Color(200, 200, 100));
                dice(i);
                boardfield();
                displayPawns();
                window.display();
                Sleep(1000);
            }
            else if (pawnOnBoard > 0) {
                for (int j = 0; j < 4; j++)
                    if (tab[player * 4 + j] == 1) h = j;
                for (int a = 0; a < i; a++) {
                    window.clear(sf::Color(200, 200, 100));
                    dice(i);
                    boardfield();
                    if (player == 1) {
                        pawns[player * 4 + h].X -= cordsY[pawns[player * 4 + h].index + a];
                        pawns[player * 4 + h].Y += cordsX[pawns[player * 4 + h].index + a];
                    }
                    else if (player == 2) {
                        pawns[player * 4 + h].X -= cordsX[pawns[player * 4 + h].index + a];
                        pawns[player * 4 + h].Y -= cordsY[pawns[player * 4 + h].index + a];
                    }
                    else if (player == 3) {
                        pawns[player * 4 + h].X += cordsY[pawns[player * 4 + h].index + a];
                        pawns[player * 4 + h].Y -= cordsX[pawns[player * 4 + h].index + a];
                    }
                    displayPawns();
                    window.display();
                    Sleep(250);
                }
                pawns[player * 4 + h].index += i;
                n = -1;
                player++;
                if (player == 4) player = 0;
            }
            else {
                n = -1;
                player++;
                if (player == 4) player = 0;
                dice(i);
                boardfield();
                displayPawns();
                window.display();
                Sleep(1000);
            }
        }
    }
    else {     // 0 pawns on the board
        if (i == 6) {
            for (int j = 0; j < 4; j++)
                if (tab[player * 4 + j] == 0) {
                    if (player == 1) {
                        pawns[player * 4 + j].X = WIDTH / 2 - 460;
                        pawns[player * 4 + j].Y = HEIGHT / 2 - 145;
                    }
                    else if (player == 2) {
                        pawns[player * 4 + j].X = WIDTH / 2 + 65;
                        pawns[player * 4 + j].Y = HEIGHT / 2 - 460;
                    }
                    else if (player == 3) {
                        pawns[player * 4 + j].X = WIDTH / 2 + 380;
                        pawns[player * 4 + j].Y = HEIGHT / 2 + 65;
                    }
                    tab[player * 4 + j] = 1;
                    break;
                }
            window.clear(sf::Color(200, 200, 100));
            dice(i);
            boardfield();
            displayPawns();
            window.display();
            Sleep(1000);
        }
        else {
            n = -1;
            player++;
            if (player == 4) player = 0;
            Sleep(1000);
        }
    }
    for (int j = 0; j < 4; j++)
        if (pawns[player * 4 + j].X == WIDTH / 2 - 40 && pawns[player * 4 + j].Y == HEIGHT / 2 - 40) {     // pawn reaches the finish line
            pawns[player * 4 + j].Y = 1000;
            tab[player * 4 + j] = 2;
        }
    n++;
    if (n >= 3) {     // max 3 throws
        n = 0;
        player++;
        if (player == 4) player = 0;
    }
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
    text5.setPosition(750, 800);
    text5.setFillColor(sf::Color::Black);
    text5.setCharacterSize(20);
    sf::CircleShape triangle(30, 3);     //pawn
    triangle.setPosition(475, 128);
    triangle.setFillColor(sf::Color::Red);
    shape8.setPosition(489,120);
    shape8.setFillColor(sf::Color::Red);
    neutral.setFillColor(sf::Color(160,160,160));
    neutral.setSize(sf::Vector2f(30, 30));
    neutral.setOutlineThickness(5);
    neutral.setOutlineColor(sf::Color::Black);
    neutral.setPosition(755, 750);
    sf::Text text6("grey is a neutral field", font);
    text6.setPosition(800, 750);
    text6.setFillColor(sf::Color::Black);
    text6.setCharacterSize(20);
    for (int i = 0; i < 4; i++) {     // pawns setup
        pawns[i].color = "Red";
        pawns[i+4].color = "Blue";
        pawns[i+8].color = "Yellow";
        pawns[i+12].color = "Green";
        pawns[i].index = 0;
        pawns[i+4].index = 0;
        pawns[i+8].index = 0;
        pawns[i+12].index = 0;
    }
    for (int i = 0; i < 16; i++) {
        pawns[i].X = tabx[i];
        pawns[i].Y = taby[i];
    }

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
            window.draw(square);
            window.draw(neutral);
            dice(i);
            i++;
            if (i == 7) i = 1;
            window.display();
        }
        else     // game        
        {
           
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
                if (player == 0) gamer();
                else robotGamers();
                result = true;
            }
            else i++;
            if (i == 7) i = 1;
            window.clear(sf::Color(200, 200, 100));
            boardfield();
            dice(i);
            displayPawns();
            window.display();
        }               
    }
    return 0;
}