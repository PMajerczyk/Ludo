#include <SFML/Graphics.hpp>
#include <string.h>

class Board : public sf::RectangleShape
{
	public:
	void field(float , float, int=200, int=200, int=100);
};

class Pawn : public sf::CircleShape
{
	public:
	int X;
	int Y;
	std::string color;
	int index;
	void pawn();
};