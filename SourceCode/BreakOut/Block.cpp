// code taken from http://www.edparrish.net/cs11/13f/lesson12.php#12.2
#include <cmath>
#include "block.h"
#include "stdafx.h"
#include <stdio.h>

Block::Block()
{
    const float SPEED = .025f;
    circ = sf::RectangleShape(sf::Vector2f(100, 20));
    circ.setFillColor(sf::Color::Green);
    dx = SPEED;
    dy = SPEED;
	show = true;
}

Block::Block(float x, float y, float speedx, float speedy, float rad, sf::Color ballColor)
{
	circ = sf::RectangleShape(sf::Vector2f(60, 20));// CircleShape(rad);
    circ.setFillColor(ballColor);
    circ.setPosition(x, y);
    dx = 0;//speedx;
    dy = 25;//speedy;
	radius = rad;
	show = true;
}

Block::~Block(){

}

void Block::setSpeed(float x, float y){
	dx = x;
	dy = y;
}

void Block::update(sf::RenderWindow& win)
{
	constrain(win);
    circ.move(dx, dy);
}

void Block::draw(sf::RenderWindow& win)
{
	win.draw(circ);
}

sf::Color Block::getColor(){
	return circ.getFillColor();
}


void Block::moveDown(sf::RenderWindow& win){
	// move towards left
	dy = 0;
	dx = 0;
	constrain(win);
	circ.move(dx, dy);
}

void Block::constrain(sf::RenderWindow& win){
	
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

sf::Vector2f Block::currentPosition(){
	return circ.getPosition();
}

float Block::getRad(){
	return 10;//circ.getRadius();
}

void Block::updateColor(sf::Color c){
	circ.setFillColor(c);
}

sf::Vector2f Block::getSize(){
	return circ.getSize();
}