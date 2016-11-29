#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>
#include <iostream>
#include "Ball.h"
#include "Paddle.h"
#include "Brick.h"
#include <vector>
#include <random>
#define PI 3.14159265

using namespace sf;
using namespace std;

void render_frame();
void update_state();
void update_ball();
void update_paddle();
void draw_bricks();
void draw_ui();
void load_bricks();
void setScore();

RenderWindow window(VideoMode(800, 600), "Breakout");
Ball ball(10.f);
Paddle paddle(110.f, 20.f);
Paddle paddle2(110.f, 20.f);
float dt;
vector<Brick> bricks;
Brick brick1(70.f, 30.f);
Brick brick2(70.f, 30.f);
int state;
int numBricks;
int speedIncrease;
int life;
Sound paddle_collision;
SoundBuffer paddle_collision_buffer;
Sound window_collision;
SoundBuffer window_collision_buffer;
Sound brick_damage;
SoundBuffer brick_damage_buffer;
Sound brick_break;
SoundBuffer brick_break_buffer;
Sound life_loss;
SoundBuffer life_loss_buffer;
Sound level_complete;
SoundBuffer level_complete_buffer;
float uiSize;
int score;
RectangleShape life1;
RectangleShape life2;
RectangleShape life3;
Texture life_texture;
Texture cracks_texture;
Texture cracks_texture2;
Text bricks_text;
Text score_text;
Font text_font;
RectangleShape ceiling;
int pointsPerBrick;
int combobonus;
int paddle2_speed;

int main()
{
	numBricks = 50;
	speedIncrease = 30;
	state = 0;
	life = 3;
	uiSize = 50.0f;
	score = 0;
	pointsPerBrick = 100;
	combobonus = 0;
	paddle2_speed = 800;

	srand(time(NULL));

	// setup paddles
	paddle.setFillColor(Color::Magenta);
	paddle.setPosition(window.getSize().x / 2, window.getSize().y - paddle.getSize().y);

	paddle2.setFillColor(Color::Blue);
	paddle2.setPosition(window.getSize().x / 2, window.getSize().y - 2 * paddle.getSize().y);

	// setup ball
	ball.setFillColor(Color::White);
	ball.setPosition(paddle.getPosition().x, paddle.getPosition().y + paddle.getSize().y / 2);

	// setup bricks
	load_bricks();
	if (!cracks_texture.loadFromFile("cracks_texture.png")) {
		cout << "File 'cracks_texture.png' not found!" << endl;
	}
	if (!cracks_texture2.loadFromFile("cracks_texture2.png")) {
		cout << "File 'cracks_texture2.png' not found!" << endl;
	}

	// setup sounds
	if (!paddle_collision_buffer.loadFromFile("paddle_collision.wav")) {
		cout << "File 'paddle_collision.wav' not found!" << endl;
	}
	paddle_collision.setBuffer(paddle_collision_buffer);

	if (!window_collision_buffer.loadFromFile("window_collision.wav")) {
		cout << "File 'window_collision.wav' not found!" << endl;
	}
	window_collision.setBuffer(window_collision_buffer);

	if (!brick_damage_buffer.loadFromFile("brick_damage.wav")) {
		cout << "File 'brick_damage.wav' not found!" << endl;
	}
	brick_damage.setBuffer(brick_damage_buffer);

	if (!brick_break_buffer.loadFromFile("brick_break.wav")) {
		cout << "File 'brick_break.wav' not found!" << endl;
	}
	brick_break.setBuffer(brick_break_buffer);

	if (!life_loss_buffer.loadFromFile("life_loss.wav")) {
		cout << "File 'life_loss.wav' not found!" << endl;
	}
	life_loss.setBuffer(life_loss_buffer);

	if (!level_complete_buffer.loadFromFile("level_complete.wav")) {
		cout << "File 'level_complete.wav' not found!" << endl;
	}
	level_complete.setBuffer(level_complete_buffer);

	// setup ui
	if (!life_texture.loadFromFile("life_texture.png")) {
		cout << "File 'life_texture.png' not found!" << endl;
	}
	if (!text_font.loadFromFile("ARIALUNI.TTF")) {
		cout << "File 'ARIALUNI.TTF' not found!" << endl;
	}

	bricks_text.setFont(text_font);
	bricks_text.setCharacterSize(32);
	bricks_text.setOrigin(bricks_text.getLocalBounds().left + bricks_text.getLocalBounds().width / 2.f, bricks_text.getLocalBounds().top + bricks_text.getLocalBounds().height / 2.f);
	bricks_text.setPosition(window.getSize().x / 2.f, 25.f);

	score_text.setFont(text_font);
	score_text.setCharacterSize(32);
	setScore();

	life1.setTexture(&life_texture);
	life1.setSize(Vector2f(36.f, 30.f));
	life1.setOrigin(18.f, 15.f);
	life1.setPosition(25.f, 25.f);

	life2.setTexture(&life_texture);
	life2.setSize(Vector2f(36.f, 30.f));
	life2.setOrigin(18.f, 15.f);
	life2.setPosition(25.f + 36.f, 25.f);

	life3.setTexture(&life_texture);
	life3.setSize(Vector2f(36.f, 30.f));
	life3.setOrigin(18.f, 15.f);
	life3.setPosition(25.f + 2 * 36.f, 25.f);

	ceiling.setFillColor(Color::White);
	ceiling.setSize(Vector2f(800, 1));
	ceiling.setPosition(0.f, 49.f);
	
	int random;
	Clock clock;
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed) {
				window.close();
			}
		}

		dt = clock.restart().asSeconds();

		// pre play state
		if (state == 0) {
			combobonus = 0;
			update_paddle();
			ball.setPosition(paddle.getPosition().x, paddle.getPosition().y - paddle.getSize().y / 2 - 1);

			if (Mouse::isButtonPressed(Mouse::Left)) {
				state = 1;
				random = rand() % 91 - 45;
				ball.setSpeed(300 * sqrt(2));
				ball.setVelocity(ball.getSpeed() * sin(random * PI / 180), -1 * ball.getSpeed() * cos(random * PI / 180));
			}
		}
		// play state
		else if (state == 1) {
			update_state();
		}
		// gameover
		else if (state == 2) {
			life = 3;
			cout << "gameover" << endl;
			load_bricks();
			state = 0;
			score = 0;
			setScore();
		}
		// load next level
		else if (state == 3) {
			level_complete.play();
			cout << "level complete" << endl;
			load_bricks();
			state = 0;
		}

		render_frame();
	}

	return 0;
}

void load_bricks() {
	while (!bricks.empty()) {
		bricks.erase(remove(bricks.begin(), bricks.end(), bricks[0]), bricks.end());
	}

	int random;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 10; ++j) {
			bricks.push_back(Brick(70.f, 30.f));
			bricks[i * 10 + j].setOrigin(35.f, 15.f);
			bricks[i * 10 + j].setPosition(80.f * j + 40.f, uiSize + 20.f + i * 40.f);

			random = rand() % 4 + 1;
			if (random == 1) {
				bricks[i * 10 + j].setFillColor(Color::Red);
				bricks[i * 10 + j].setType(random);
			}
			else if (random == 2) {
				bricks[i * 10 + j].setFillColor(Color::Yellow);
				bricks[i * 10 + j].setType(random);
			}
			else if (random == 3) {
				bricks[i * 10 + j].setFillColor(Color::Transparent);
				bricks[i * 10 + j].setType(random);
			}
			else if (random == 4) {
				bricks[i * 10 + j].setFillColor(Color::Green);
				bricks[i * 10 + j].setType(random);
			}
		}
	}

	numBricks = 50;
	bricks_text.setString("50 remaining");
}

void update_state() {
	update_paddle();
	update_ball();
}

void update_ball() {
	Vector2f ballPos = ball.getPosition();
	Vector2f vel = ball.getVelocity();

	// bounce off window
	if (ballPos.x < 0 && vel.x < 0 || ballPos.x > window.getSize().x && vel.x > 0) {
		vel.x = -vel.x;
		window_collision.play();
	}
//	if (ballPos.y < uiSize && vel.y < 0 || ballPos.y > window.getSize().y && vel.y > 0) {
	if (ballPos.y < uiSize && vel.y < 0) {
		vel.y = -vel.y;
		window_collision.play();
	}

	// hits bottom of window
	if (ballPos.y > window.getSize().y && vel.y > 0) {
		life_loss.play();

		if (--life < 0) {
			state = 2;
			return;
		}

		state = 0;
		return;
	}

	// paddle collision
	if (vel.y > 0 && ballPos.x <= paddle.getPosition().x + paddle.getSize().x / 2 &&
		ballPos.x >= paddle.getPosition().x - paddle.getSize().x / 2 &&
		ballPos.y <= paddle.getPosition().y + paddle.getSize().y / 2 &&
		ballPos.y >= paddle.getPosition().y - paddle.getSize().y / 2) {
		Vector2f paddlePos = paddle.getPosition();
		
		// tweak paddle position y so that ball always deflects in a more upward direction
		paddlePos.y += 30;

		vel = ballPos - paddlePos;
		vel = Vector2f(ball.getSpeed() * vel.x / sqrt(vel.x * vel.x + vel.y * vel.y), ball.getSpeed() * vel.y / sqrt(vel.x * vel.x + vel.y * vel.y));
		
		paddle_collision.play();
	}

	if (vel.y > 0 && ballPos.x <= paddle2.getPosition().x + paddle2.getSize().x / 2 &&
		ballPos.x >= paddle2.getPosition().x - paddle2.getSize().x / 2 &&
		ballPos.y <= paddle2.getPosition().y + paddle2.getSize().y / 2 &&
		ballPos.y >= paddle2.getPosition().y - paddle2.getSize().y / 2) {
		Vector2f paddlePos = paddle2.getPosition();

		// tweak paddle position y so that ball always deflects in a more upward direction
		paddlePos.y += 30;

		vel = ballPos - paddlePos;
		vel = Vector2f(ball.getSpeed() * vel.x / sqrt(vel.x * vel.x + vel.y * vel.y), ball.getSpeed() * vel.y / sqrt(vel.x * vel.x + vel.y * vel.y));

		paddle_collision.play();
	}

	// brick collision
	for (int i = 0; i < bricks.size(); ++i) {
		if (ballPos.x <= bricks[i].getPosition().x + bricks[i].getSize().x / 2 &&
			ballPos.x >= bricks[i].getPosition().x - bricks[i].getSize().x / 2 &&
			ballPos.y <= bricks[i].getPosition().y + bricks[i].getSize().y / 2 &&
			ballPos.y >= bricks[i].getPosition().y - bricks[i].getSize().y / 2) {
			Vector2f brickPos = bricks[i].getPosition();

			// tweak paddle position y so that ball always deflects in a more upward direction
			if (ballPos.y < brickPos.y) {
				brickPos.y += 30;
			}
			else {
				brickPos.y -= 30;
			}

			if (bricks[i].getType() == 1 || bricks[i].getType() == 3) {
				brick_break.play();
				bricks.erase(remove(bricks.begin(), bricks.end(), bricks[i]), bricks.end());
				bricks_text.setString(to_string(--numBricks) + " remaining");
				bricks_text.setOrigin(bricks_text.getLocalBounds().left + bricks_text.getLocalBounds().width / 2.f, bricks_text.getLocalBounds().top + bricks_text.getLocalBounds().height / 2.f);
				score += pointsPerBrick + combobonus;
				combobonus += 10;
				setScore();
			}
			else if (bricks[i].getType() == 2) {
				brick_damage.play();
				if (rand() % 2) {
					bricks[i].setTexture(&cracks_texture);
				}
				else {
					bricks[i].setTexture(&cracks_texture2);
				}
				bricks[i].setType(1);
			}
			else if (bricks[i].getType() == 4) {
				brick_break.play();
				bricks.erase(remove(bricks.begin(), bricks.end(), bricks[i]), bricks.end());
				ball.setSpeed(ball.getSpeed() + speedIncrease);
				bricks_text.setString(to_string(--numBricks) + " remaining");
				bricks_text.setOrigin(bricks_text.getLocalBounds().left + bricks_text.getLocalBounds().width / 2.f, bricks_text.getLocalBounds().top + bricks_text.getLocalBounds().height / 2.f);
				score += pointsPerBrick + combobonus;
				combobonus += 10;
				setScore();
			}

			if (numBricks == 0) {
				state = 3;
				return;
			}

			vel = ballPos - brickPos;
			vel = Vector2f(ball.getSpeed() * vel.x / sqrt(vel.x * vel.x + vel.y * vel.y), ball.getSpeed() * vel.y / sqrt(vel.x * vel.x + vel.y * vel.y));
		}
	}

	ball.setVelocity(vel);
	ball.setPosition(ballPos + vel * dt);
}

void update_paddle() {
	// paddle 1
	Vector2i mousePos = Mouse::getPosition(window);
	Vector2f paddlePos = paddle.getPosition();
	paddlePos.x = mousePos.x;

	// keep paddle inside window
	if (paddlePos.x - paddle.getSize().x / 2 < 0) {
		paddlePos.x = paddle.getSize().x / 2;
	}
	if (paddlePos.x + paddle.getSize().x / 2 > window.getSize().x) {
		paddlePos.x = window.getSize().x - paddle.getSize().x / 2;
	}

	paddle.setPosition((float) paddlePos.x, (float) paddlePos.y);

	// paddle 2
	paddlePos = paddle2.getPosition();
	if (Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) {
		paddlePos.x -= paddle2_speed * dt;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) {
		paddlePos.x += paddle2_speed * dt;
	}

	// keep paddle inside window
	if (paddlePos.x - paddle2.getSize().x / 2 < 0) {
		paddlePos.x = paddle.getSize().x / 2;
	}
	if (paddlePos.x + paddle2.getSize().x / 2 > window.getSize().x) {
		paddlePos.x = window.getSize().x - paddle2.getSize().x / 2;
	}

	paddle2.setPosition((float)paddlePos.x, (float)paddlePos.y);
}

void render_frame() {
	window.clear();
	paddle.draw(window);
	paddle2.draw(window);
	draw_bricks();
	ball.draw(window);
	draw_ui();
	window.display();
}

void setScore() {
	score_text.setString(to_string(score));
	score_text.setOrigin(score_text.getLocalBounds().left + score_text.getLocalBounds().width / 2.f, score_text.getLocalBounds().top + score_text.getLocalBounds().height / 2.f);
	score_text.setPosition(window.getSize().x - score_text.getLocalBounds().width, uiSize / 2.f);
}

void draw_bricks() {
	for (int i = 0; i < bricks.size(); ++i) {
		bricks[i].draw(window);
	}
}

void draw_ui() {
	if (life > 0) {
		window.draw(life1);
	}
	if (life > 1) {
		window.draw(life2);
	}
	if (life > 2) {
		window.draw(life3);
	}
	window.draw(bricks_text);
	window.draw(ceiling);
	window.draw(score_text);
}