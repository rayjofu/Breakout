#include "Paddle.h"

using namespace sf;

Paddle::Paddle() {
	paddle = RectangleShape();
}

Paddle::Paddle(float width, float height) {
	paddle = RectangleShape(Vector2f(width, height));
	paddle.setOrigin(width / 2, height / 2);
}

void Paddle::setFillColor(Color color) {
	paddle.setFillColor(color);
}

void Paddle::setOrigin(float x, float y) {
	paddle.setOrigin(x, y);
}

void Paddle::setPosition(float x, float y) {
	paddle.setPosition(x, y);
}

Vector2f Paddle::getPosition() {
	return paddle.getPosition();
}

void Paddle::setSize(float x, float y) {
	paddle.setSize(Vector2f(x, y));
}

Vector2f Paddle::getSize() {
	return paddle.getSize();
}

void Paddle::draw(RenderWindow& window) {
	window.draw(paddle);
}
