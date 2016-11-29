#include "Brick.h"

using namespace sf;
using namespace std;

Brick::Brick() {
	brick = RectangleShape();
}

Brick::Brick(float width, float height) {
	brick = RectangleShape(Vector2f(width, height));
	brick.setOrigin(width / 2, height / 2);
}

void Brick::setFillColor(Color color) {
	brick.setFillColor(color);
}

void Brick::setOrigin(float x, float y) {
	brick.setOrigin(x, y);
}

void Brick::setPosition(float x, float y) {
	brick.setPosition(x, y);
}

Vector2f Brick::getPosition() {
	return brick.getPosition();
}

void Brick::setSize(float x, float y) {
	brick.setSize(Vector2f(x, y));
}

Vector2f Brick::getSize() {
	return brick.getSize();
}

void Brick::setType(int t) {
	type = t;
}

int Brick::getType() {
	return type;
}

void Brick::draw(RenderWindow& window) {
	window.draw(brick);
}

void Brick::setTexture(Texture* texture) {
	brick.setTexture(texture);
}

bool Brick::operator==(const Brick& rhs) {
	return this == &rhs;
}