#pragma once

#include <SFML/Graphics.hpp>

class Ball {
public:
	Ball();
	Ball(float radius);
	void setFillColor(sf::Color color);
	void setOrigin(float x, float y);
	void setPosition(float x, float y);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setVelocity(float x, float y);
	void setVelocity(sf::Vector2f vel);
	sf::Vector2f getVelocity();
	void setSpeed(float s);
	float getSpeed();
	void setRadius(float radius);
	float getRadius();
	void draw(sf::RenderWindow& window);
private:
	sf::CircleShape ball;
	sf::Vector2f velocity;
	float speed;
};