// code taken from http://www.edparrish.net/cs11/13f/lesson12.php#12.2
#include <cmath>
#include "ball.h"
#include "stdafx.h"
#include <stdio.h>

Ball::Ball()
{
    const float SPEED = .025f;
    circ = sf::CircleShape(RADIUS);
    circ.setFillColor(sf::Color::Green);
    dx = SPEED;
    dy = SPEED;
}

Ball::Ball(float x, float y, float speedx, float speedy, float rad, sf::Color ballColor)
{
    circ = sf::CircleShape(rad);
    circ.setFillColor(ballColor);
    circ.setPosition(x, y);
    dx = 0.7f;//speedx;
    dy = 0.7f;//speedy;
	radius = rad;
	float random_integer = std::rand() % 360 + 1; //Gives random number between 1 and 360.
	_angle = random_integer;
}

Ball::~Ball(){

}

void Ball::destroy(){
	circ.setFillColor(sf::Color::Black);
	this->~Ball();
}

void Ball::setSpeed(float x, float y){
	dx = x;
	dy = y;
}

void Ball::setRad(float r){
	radius = r;
	circ.setRadius(r);
}

void Ball::update(sf::RenderWindow& win, float deltaTime)
{
	float factor = 400 * deltaTime;
//	float random_integer = std::rand() % 360 + 1; //Gives random number between 1 and 360.
//	_angle = random_integer;
   
	
	//dx = std::cos(_angle) * factor;
	//dy = std::sin(_angle) * factor;
	constrain(win);
	circ.move(dx, dy);
  //  circ.move(dx, dy);
}

void Ball::draw(sf::RenderWindow& win)
{
	win.draw(circ);
}




void Ball::constrain(sf::RenderWindow& win){
	
	sf::Vector2u winSize = win.getSize();
    sf::Vector2f pos = circ.getPosition();

    if (pos.x < 0)
    {
        dx = std::abs(dx);
    }
    else if (pos.x + RADIUS * 2 > winSize.x)
    {
        dx = -std::abs(dx);
    }
	 if (pos.y < 0)
    {
        dy = std::abs(dy);
    }
    else if (pos.y + RADIUS * 2 > winSize.y)
    {
	//	 _angle =  180 - _angle;
        dy = -std::abs(dy);
    }
}

sf::Vector2f Ball::currentPosition(){
	return circ.getPosition();
}

float Ball::getRad(){
	return circ.getRadius();
}

void Ball::updateColor(sf::Color c){
	circ.setFillColor(c);
}