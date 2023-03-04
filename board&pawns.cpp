#include "board&pawns.h"

void Board::field(float x, float y, int c1, int c2, int c3)
{
    RectangleShape::setFillColor(sf::Color(c1, c2, c3));
    RectangleShape::setSize(sf::Vector2f(100, 100));
    RectangleShape::setOutlineThickness(5);
    RectangleShape::setOutlineColor(sf::Color::Black);
    RectangleShape::setPosition(x, y);
}


void Pawn::pawn()
{
    CircleShape::setRadius(40);
    if (color == "Red") CircleShape::setFillColor(sf::Color::Red);
    if (color == "Blue") CircleShape::setFillColor(sf::Color::Blue);
    if (color == "Yellow") CircleShape::setFillColor(sf::Color::Yellow);
    if (color == "Green") CircleShape::setFillColor(sf::Color::Green);
    CircleShape::setOutlineThickness(5);
    CircleShape::setOutlineColor(sf::Color::Black);
    CircleShape::setPosition(X, Y);
}