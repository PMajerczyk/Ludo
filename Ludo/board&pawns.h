#include <SFML/Graphics.hpp>

class Board : public sf::RectangleShape
{
public:

	Board(float x , float y, int c1 = 200, int c2 = 200, int c3 = 100);

	Board(float x, float y, const sf::Color& c);

	Board() = default;

	~Board() = default;

	void set_cords(float x, float y) { RectangleShape::setPosition(x, y); }

	void set_color(int c1, int c2, int c3) { RectangleShape::setFillColor(sf::Color(c1, c2, c3)); }
};

class Pawn : public sf::CircleShape
{
public:

	Pawn(float x, float y, const sf::Color& c);

	Pawn() = default;

	~Pawn() = default;

	void pawn(bool = false);

	int getX() const { return X; }

	void setX(int x) { X = x; }

	int getY() const { return Y; }

	void setY(int y) { Y = y; }

	int getIdx() const { return index; }

	void setIdx(int idx) { index = idx; }

private:

	int X;
	int Y;
	int index = 0;
};