#pragma once
#include <SFML/Graphics.hpp>

class Brick {
public:
	Brick();
	Brick(float width, float height);
	void setFillColor(sf::Color color);
	void setOrigin(float x, float y);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setSize(float x, float y);
	sf::Vector2f getSize();
	void setType(int t);
	int getType();
	void setTexture(sf::Texture *t);
	void draw(sf::RenderWindow& window);
	bool operator==(const Brick& rhs);
private:
	sf::RectangleShape brick;
	int type;
};