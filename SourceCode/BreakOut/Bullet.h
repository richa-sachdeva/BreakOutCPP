#include "stdafx.h"
#include <SFML/Graphics.hpp>

#ifndef BULLET_H
#define BULLET_H

const float BULLET_RADIUS = 10.f;
const float BULLET_SPEED = 0.65f;

class Bullet
{
public:
    Bullet();
	Bullet(float x, float y);
	~Bullet();
    void update(sf::RenderWindow& win);
    void draw(sf::RenderWindow& win);

	void destroy();

	void setPosition(float x, float y);
	void setSpeed(float x, float y);

	float getSpeedX(){return dx;}
	float getSpeedY(){return dy;}

	sf::Vector2f currentPosition();
	sf::Vector2f getRad();
	//sf::
	void updateColor(sf::Color c);

	sf::Color getColor();

	sf::Vector2f getSize();

	bool IsShown(){ return shown;}
	void SetShown(bool val){ shown = val;}

	bool IsServer(){ return playerType;}
	void SetPlayServer(bool val){ playerType = val;}

private:
	void constrain(sf::RenderWindow& win);

 //   sf::CircleShape circ;
	sf::RectangleShape circ;
	//EllipseShape circ;
    float radius, dx, dy;

	bool shown;
	bool playerType;
};
#endif