// code taken from http://www.edparrish.net/cs11/13f/lesson12.php#12.2
#include <cmath>
#include "paddle.h"
#include "stdafx.h"
#include <stdio.h>

Paddle::Paddle()
{
    const float SPEED = .025f;
    circ = sf::RectangleShape(sf::Vector2f(100, 20));
    circ.setFillColor(sf::Color::Green);
    dx = SPEED;
    dy = SPEED;
}

Paddle::Paddle(float x, float y, float speedx, float speedy, float rad, sf::Color ballColor)
{
	circ = sf::RectangleShape(sf::Vector2f(80, 20));// CircleShape(rad);
    circ.setFillColor(ballColor);
    circ.setPosition(x, y);
    dx = 4;//speedx;
    dy = 4;//speedy;
	radius = rad;
}

Paddle::~Paddle(){

}

void Paddle::setSpeed(float x, float y){
	dx = x;
	dy = y;
}

void Paddle::update(sf::RenderWindow& win)
{
	constrain(win);
    circ.move(dx, dy);
}

void Paddle::draw(sf::RenderWindow& win)
{
	win.draw(circ);
}

void Paddle::moveLeft(sf::RenderWindow& win){
	// move towards left
	dx += -3;
	dy = 0;
	
	if( dx < -MAX_VELOCITY)
		dx = -MAX_VELOCITY;

	constrain(win);
	circ.move(dx, dy);
}

void Paddle::moveRight(sf::RenderWindow& win){
	// move towards left
	dx += 3;
	dy = 0;
	
	if( dx > MAX_VELOCITY)
		dx = MAX_VELOCITY;

	constrain(win);
	circ.move(dx, dy);
}

void Paddle::moveUp(sf::RenderWindow& win){
	// move towards left
	dy = -3;
	dx = 0;
	constrain(win);
	circ.move(dx, dy);
}

void Paddle::moveDown(sf::RenderWindow& win){
	// move towards left
	dy = 0;
	dx = 0;
	constrain(win);
	circ.move(dx, dy);
}

void Paddle::constrain(sf::RenderWindow& win){
	
	sf::Vector2u winSize = win.getSize();
    sf::Vector2f pos = circ.getPosition();

    if (pos.x < 0)
    {
        dx = std::abs(dx);
    }
    else if (pos.x + 80 > winSize.x)
    {
        dx = -std::abs(dx);
    }
	 if (pos.y < 0)
    {
        dy = std::abs(dy);
    }
    else if (pos.y + 20 > winSize.y)
    {
        dy = -std::abs(dy);
    }
}

sf::Vector2f Paddle::currentPosition(){
	return circ.getPosition();
}

float Paddle::getRad(){
	return 10;//circ.getRadius();
}

void Paddle::updateColor(sf::Color c){
	circ.setFillColor(c);
}

sf::Vector2f Paddle::getSize(){
	return circ.getSize();
}