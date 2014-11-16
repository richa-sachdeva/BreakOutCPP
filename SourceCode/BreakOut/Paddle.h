#include "stdafx.h"
#include <SFML/Graphics.hpp>
#ifndef PADDLE_H
#define PADDLE_H

const float LENGTH = 10.f;
//const float MAX_VELOCITY = 10.0f;

class Paddle
{
public:
    Paddle();
    Paddle(float x, float y, float speedx, float speedy, float radius, sf::Color ballColor);
	~Paddle();
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);

	void moveLeft(sf::RenderWindow& win);
	void moveRight(sf::RenderWindow& win);
	void moveUp(sf::RenderWindow& win);
	void moveDown(sf::RenderWindow& win);

	void setSpeed(float x, float y);

	sf::Vector2f currentPosition();
	float getRad();

	void updateColor(sf::Color c);
	sf::Vector2f getSize();
	

private:
	void constrain(sf::RenderWindow& win);

	sf::RectangleShape circ;
	sf::CircleShape bullet;
    float radius, dx, dy;
};
#endif