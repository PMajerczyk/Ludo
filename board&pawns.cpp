#include "board&pawns.h"

void Board::field(float x, float y, int c1, int c2, int c3)
{
    RectangleShape::setFillColor(sf::Color(c1, c2, c3));
    RectangleShape::setSize(sf::Vector2f(100, 100));
    RectangleShape::setOutlineThickness(5);
    RectangleShape::setOutlineColor(sf::Color::Black);
    RectangleShape::setPosition(x, y);
}


void Pawn::pawn(float x, float y, static const sf::Color color)
{
    CircleShape::setRadius(40);
    CircleShape::setFillColor(color);
    CircleShape::setOutlineThickness(5);
    CircleShape::setOutlineColor(sf::Color::Black);
    CircleShape::setPosition(x, y);
}