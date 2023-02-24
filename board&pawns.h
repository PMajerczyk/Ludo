#include <SFML/Graphics.hpp>

class Board : public sf::RectangleShape
{
	public:
	void field(float , float, int=200, int=200, int=100);
};

class Pawn : public sf::CircleShape
{
	public:
	void pawn(float, float, static const sf::Color color);
};