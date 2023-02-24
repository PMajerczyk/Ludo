#include "board&pawns.h"

void board::field(float x, float y, int c1, int c2, int c3)
{
    RectangleShape::setFillColor(sf::Color(c1, c2, c3));
    RectangleShape::setSize(sf::Vector2f(100, 100));
    RectangleShape::setOutlineThickness(5);
    RectangleShape::setOutlineColor(sf::Color::Black);
    RectangleShape::setPosition(x, y);
}