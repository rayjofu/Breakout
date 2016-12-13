#pragma once

#include <SFML/Graphics.hpp>

class Paddle {
public:
	Paddle();
	Paddle(float width, float height);
	void setFillColor(sf::Color color);
	void setOrigin(float x, float y);
	void setPosition(float x, float y);
	sf::Vector2f getPosition();
	void setSize(float x, float y);
	sf::Vector2f getSize();
	void draw(sf::RenderWindow& window);
private:
	sf::RectangleShape paddle;
};