#include "stdafx.h"
#include <SFML/Graphics.hpp>
#ifndef BALL_H
#define BALL_H

const float RADIUS = 10.f;
const float HALF_RAD = 6.0f;
const float MAX_VELOCITY = 10.0f;

class Ball
{
public:
    Ball();
    Ball(float x, float y, float speedx, float speedy, float radius, sf::Color ballColor);
	~Ball();
	void destroy();
    void update(sf::RenderWindow& win, float deltaTime);
    void draw(sf::RenderWindow& win);

	void setSpeed(float x, float y);
	float getSpeedX(){ return dx;}
	float getSpeedY(){ return dy;}

	sf::Vector2f currentPosition();
	float getRad();
	void setRad(float r);

	void updateColor(sf::Color c);
	

private:
	void constrain(sf::RenderWindow& win);
	float LinearVelocityX(float angle);
	float LinearVelocityY(float angle);

    sf::CircleShape circ;
    float radius, dx, dy;
	float _velocity, _angle;
};
#endif