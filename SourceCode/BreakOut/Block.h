#include "stdafx.h"
#include <SFML/Graphics.hpp>
#ifndef BLOCK_H
#define BLOCK_H

//const float LENGTH = 10.f;
//const float MAX_VELOCITY = 7.0f;

class Block
{
public:
    Block();
    Block(float x, float y, float speedx, float speedy, float radius, sf::Color ballColor);
	~Block();
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);

	void moveDown(sf::RenderWindow& win);

	void setSpeed(float x, float y);

	sf::Vector2f currentPosition();
	float getRad();

	void updateColor(sf::Color c);
	sf::Vector2f getSize();
	
	sf::Color getColor();
	bool GetShow(){return show;}
	void SetShow(bool b){show = b;}

private:
	void constrain(sf::RenderWindow& win);

	sf::RectangleShape circ;
	sf::CircleShape bullet;
    float radius, dx, dy;
	bool show;
};
#endif