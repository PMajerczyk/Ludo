#include "board&pawns.h"

Board::Board(float x, float y, int c1, int c2, int c3) 
{
    RectangleShape::setFillColor(sf::Color(c1, c2, c3));
    RectangleShape::setSize(sf::Vector2f(100, 100));
    RectangleShape::setOutlineThickness(5);
    RectangleShape::setOutlineColor(sf::Color::Black);
    RectangleShape::setPosition(x, y);
}

Board::Board(float x, float y, const sf::Color& c)
{
    RectangleShape::setFillColor(c);
    RectangleShape::setSize(sf::Vector2f(100, 100));
    RectangleShape::setOutlineThickness(5);
    RectangleShape::setOutlineColor(sf::Color::Black);
    RectangleShape::setPosition(x, y);
}                                          


Pawn::Pawn(float x, float y, const sf::Color& c) : X(x), Y(y)
{
    CircleShape::setRadius(40);
    CircleShape::setFillColor(c);
    CircleShape::setOutlineThickness(5);
    CircleShape::setOutlineColor(sf::Color::Black);
    CircleShape::setPosition(X, Y);
}

void Pawn::pawn(bool light)
{
    if (light == true) {
        CircleShape::setOutlineThickness(7);
        CircleShape::setOutlineColor(sf::Color::White);
    }
    else {
        CircleShape::setOutlineThickness(5);
        CircleShape::setOutlineColor(sf::Color::Black);
    }
    CircleShape::setPosition(X, Y);
}