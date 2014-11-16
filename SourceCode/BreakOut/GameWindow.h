#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>

#include "Ball.h"
#include "Paddle.h"
#include "Block.h"
#include "Bullet.h"

static const int SCREEN_WIDTH = 700;
static const int SCREEN_HEIGHT = 600;

class GameWindow 
{
public:
	GameWindow();
	~GameWindow();


	void Start(bool debug);
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();
	
	int GetScreenWidth();
	int GetScreenHeight();

	void UpdateGameWindow();

	void fire(float, float, sf::RenderWindow& win, bool);
	void shoot(float, float, sf::RenderWindow& win, bool);

//	bool circleTest(Coin& object1, Bullet& object2);
//	bool playerTest(Ball& player, Bullet& obj);
//	bool serverTest(ServerPlayer& server, Bullet& obj);

private:
	bool IsExiting();
	void GameLoop(bool debug);

	void ShowWindow();
	void ClearWindow();
	void DrawWindow();
	sf::Color ColorFromChar(char c);
	sf::Color GetRandomColor();
	sf::Color GetRandomBlockColor();

//	void TestServerBullets(Coin& object1);
//	bool TestPlayerBullets(Coin& object1);
	bool PaddleBallCollision(Paddle& , Ball& ); // To check the collision between paddle and ball, and if it's there, 
												// reverse ball position or game is lost
	bool BallBelowPaddle(Paddle&, Ball&);

	bool BallBlockCollision(Ball&, Block&); // To check collision between ball and different kind of blocks -> 4 different kind of blocks
	bool BallBulletCollision(Ball&, Bullet&);
	//void HideBullet(Bullet& b);
	void GameOver();
	// Private Variables

	enum GameState { Uninitialized, ShowingStartUpScreen, Paused, 
					ShowingMenu, Playing, Exiting };

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;


	Ball b2;
	Paddle p1;

	std::vector<Block> blockList;
//	std::list<Bullet> bulletList; 
	std::vector<Bullet> bulletList;
	
	std::vector<bool> showBullet;
	std::string data;
	
	int playerLives; 
	float  timeSum;
	bool gamePlay, debugPlay;
};