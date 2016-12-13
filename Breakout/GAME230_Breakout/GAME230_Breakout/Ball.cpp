#include "Ball.h"

using namespace sf;

Ball::Ball() {
	ball = CircleShape();
}

Ball::Ball(float radius) {
	ball = CircleShape(radius);
	ball.setOrigin(radius, radius);
}

void Ball::setFillColor(Color color) {
	ball.setFillColor(color);
}

void Ball::setOrigin(float x, float y) {
	ball.setOrigin(x, y);
}

void Ball::setPosition(float x, float y) {
	ball.setPosition(x, y);
}

void Ball::setPosition(Vector2f pos) {
	ball.setPosition(pos);
}

Vector2f Ball::getPosition() {
	return ball.getPosition();
}

void Ball::setVelocity(float x, float y) {
	velocity = Vector2f(x, y);
}

void Ball::setVelocity(Vector2f vel) {
	velocity = vel;
}

Vector2f Ball::getVelocity() {
	return velocity;
}

void Ball::setSpeed(float s) {
	speed = s;
}

float Ball::getSpeed() {
	return speed;
}

void Ball::setRadius(float radius) {
	ball.setRadius(radius);
}

float Ball::getRadius() {
	return ball.getRadius();
}

void Ball::draw(RenderWindow& window) {
	window.draw(ball);
}
