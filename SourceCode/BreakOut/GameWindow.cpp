#include "stdafx.h"
#include "GameWindow.h"

GameWindow::GameWindow(){
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,32),"BreakOut!");
	this->ClearWindow();
	this->ShowWindow();
	bulletList = std::vector<Bullet>();
	blockList = std::vector<Block>();
	showBullet = std::vector<bool>();
	playerLives = 0;
	timeSum = 0.0f;
}

void GameWindow::ClearWindow(){
	_mainWindow.clear();
}

void GameWindow::ShowWindow(){
	_mainWindow.display();
}

void GameWindow::DrawWindow(){
	// add the players and draw....pretty much like repaint function!!!
//	_mainWindow.draw(m_Client->GetClientPlayer());
}

void GameWindow::UpdateGameWindow(){
	this->ClearWindow();
	this->ShowWindow();
	
	this->DrawWindow();

}

GameWindow::~GameWindow()
{
}

sf::RenderWindow& GameWindow::GetWindow(){
	return _mainWindow;
}

int GameWindow::GetScreenWidth(){
	return SCREEN_WIDTH;
}

int GameWindow::GetScreenHeight(){
	return SCREEN_HEIGHT;
}



void GameWindow::Start(bool debug){
	
	gamePlay = true;
	p1 = Paddle(SCREEN_WIDTH/2, SCREEN_HEIGHT - 3*RADIUS, 0, 0, RADIUS, sf::Color::White); 
	b2 = Ball(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 + 50, 0, 0, RADIUS, sf::Color::Cyan);

	// block data to be read from a file..data basically like
	std::string line;
	std::ifstream myfile ("blocklayout.txt");
	  if (myfile.is_open())
	  {
		while ( getline (myfile,line) )
		{
		  //std::cout << line << '\n';
		  data += line+"\n";
		}
		myfile.close();
	  } else std::cout << "Unable to open file"; 

	//  std::cout<< data;
	
	  int x = 10, y = 100, xoffset = 70, yoffset = 25;
	  for (int i = 0; i < data.length(); i++){
		  char c = data[i];
		  if(c == '\n'){
			y -= yoffset;
			x = 10;
			  continue;
		  }
		blockList.push_back(Block(x, y, 0, 0, 10, ColorFromChar(c)));
		x += xoffset;
	}

	GameLoop(debug);
}

sf::Color GameWindow::ColorFromChar(char c){
	 sf::Color col;// = Random color
	 if(c == 'R')col = sf::Color::Red;
	 else if(c == 'O') col= sf::Color::Magenta;
	 else if (c == 'Y') col = sf::Color::Yellow;
	 else if(c == 'G') col = sf::Color::Green;

	 return col;
}

void GameWindow::GameLoop(bool debug){
	
	sf::Clock clock;
	sf::Time elapsed;
	float counter = 0.85;
	float moveBlockTime = 0.15f;
	bool onceDec = false, onceInc = false;
	debugPlay = debug;

	while (_mainWindow.isOpen())
    {
        sf::Event event;
		float deltaTime = clock.restart().asSeconds();

        while (_mainWindow.pollEvent(event))
        {
			switch (event.type)
			{
				case sf::Event::Closed:
					_mainWindow.close();
					break;
				case sf::Event::KeyPressed:
					if(event.key.code == sf::Keyboard::Left)
					{
						p1.moveLeft(_mainWindow);
						break;
					}
					else if(event.key.code == sf::Keyboard::Right){
						p1.moveRight(_mainWindow);
						break;
					}
				default:	
					break;
			}
        }
	
         // Update
		b2.update(_mainWindow, deltaTime);

		for(unsigned int i=0; i<bulletList.size(); ++i){
			bulletList[i].update(_mainWindow);
			if(bulletList[i].getColor() == sf::Color::Black){
				bulletList.erase(bulletList.begin()+i);
				continue;
			}
			if(BallBulletCollision(b2, bulletList[i])){
				// destroy the ball -> game over
				if(!onceDec){
					float x = b2.getSpeedX();
					float y = b2.getSpeedY();
					x = x + 0.3;
					y = y + 0.3;
					b2.setSpeed(x, y);
					b2.setRad(HALF_RAD);
					onceDec = true;
					onceInc = false;
				}else{
					 GameOver();
				}
			}
		}

		elapsed = clock.getElapsedTime();
		timeSum += elapsed.asSeconds();
		if(timeSum > moveBlockTime){
			// move all the blocks
			for (unsigned int i=0; i<blockList.size(); ++i)
			{
				blockList[i].update(_mainWindow);
			}
			// adding itself to it
			//moveBlockTime += 0.5f;
			timeSum = 0.0f;
			// whenever the block is moved, add a line at top -> randomly generated -> can make it random here
			int x = 10, y = 25, xoffset = 70, yoffset = 25;
		    for (int i = 0; i < 10; i++){
			 blockList.push_back(Block(x, y, 0, 0, 10,GetRandomBlockColor()));
			 x += xoffset;
		   }
		}
		
		PaddleBallCollision(p1, b2);
		BallBelowPaddle(p1, b2);

		

		if(gamePlay || debug)
		{
			_mainWindow.clear();
			elapsed = clock.getElapsedTime();
		
			p1.draw(_mainWindow);
			b2.draw(_mainWindow);

			for(unsigned int i=0; i<bulletList.size(); ++i){
				Bullet bul = bulletList[i];
				bul.draw(_mainWindow);
			}

			for (unsigned int i=0; i<blockList.size(); ++i)
			{	
				Block l = blockList[i];
				sf::Color blockColor = l.getColor();
				if(BallBlockCollision(b2, l)){
					// check based on color
				
					if(blockColor == sf::Color::Yellow){
						// yellow -> destroy the block
						blockList.erase(blockList.begin()+i);
					} else if(blockColor == sf::Color::Red){
						// red -> slow down the ball
					
						if(!onceInc){
							float x = b2.getSpeedX();
							float y = b2.getSpeedY();
							x = x - 0.25;
							y = y - 0.25;
							b2.setSpeed(x, y);
							b2.setRad(RADIUS);
							onceInc = true;
							onceDec = false;
						}
					
						blockList.erase(blockList.begin()+i);
					}else if(blockColor == sf::Color::Green){
						// green -> fire a bullet
						sf::Vector2f pos = l.currentPosition();
						fire(pos.x, pos.y, _mainWindow, true);
						blockList.erase(blockList.begin()+i);
					}else if(blockColor == sf::Color::Magenta){
						// magneta -> change brick color to yellow and ball color to random color
						blockList[i].updateColor(sf::Color::Yellow);
					//	sf::Color randomColor = GetRandomColor();
						b2.updateColor(GetRandomColor());
					}
				
				}
			//	if(l.GetShow())
					l.draw(_mainWindow);
			}
		
		
        _mainWindow.display();
		}
	}
}

sf::Color GameWindow::GetRandomBlockColor(){
	sf::Color col;
	char c =' ';
	int n = std::rand() % 4;
	if(n == 0){
		c = 'R';
	}else if(n == 1){
		c = 'O';
	}else if(n == 2){
		c = 'Y';
	}else if(n == 3){
		c = 'G';
	}

	col =  ColorFromChar(c);
	return col;
}

sf::Color GameWindow::GetRandomColor(){
	sf::Color col;
	float r = std::rand() % 256 + 1; //std::rand() % 255, std::rand() % 255, std::rand() % 255
	float g = std::rand() % 256 + 1;
	float b = std::rand() % 256 + 1;
	col = sf::Color(r,g,b,255);
	return col;
}



bool GameWindow::IsExiting()
{
   if(_gameState == Exiting) 
     return true;
   else 
     return false;
}

void GameWindow::GameOver(){
	// here show Game Over Image
	gamePlay = false;
	sf::Texture image;
	if(!debugPlay){

	if(image.loadFromFile("images/Game-Lose.png") != true)
	{
		return;
	}

	sf::Sprite sprite(image);
	
	_mainWindow.clear();
	_mainWindow.draw(sprite);
	 _mainWindow.display();
	}
}

/*
void GameWindow::HideBullet(Bullet& b){
	b.setSpeed(0, 0);
	b.updateColor(sf::Color::Black);
	b.SetShown(false);

}
*/

void GameWindow::fire(float posX, float posY, sf::RenderWindow& _mainWindow, bool player){

	Bullet bullet = Bullet(posX, posY);
	bullet.setSpeed(0, BULLET_SPEED);
	bulletList.push_back(bullet);
	
}

bool GameWindow::BallBulletCollision(Ball& ball, Bullet& bullet){
	bool collide = false;

	sf::Vector2f bulletPos = bullet.currentPosition();
	sf::Vector2f ballPos = ball.currentPosition();

	sf::Vector2f bulletDimn = bullet.getSize();
	float ballRad = ball.getRad();
	
	sf::RectangleShape bulletS = sf::RectangleShape(bulletDimn);
	sf::RectangleShape ballS = sf::RectangleShape(sf::Vector2f(ballRad, ballRad));

	bulletS.setPosition(bulletPos);
	ballS.setPosition(ballPos);

	if(bulletS.getGlobalBounds().intersects(ballS.getGlobalBounds())){
		collide = true;
//		std::cout<<"collision";
	}
	return collide;
}

bool GameWindow::BallBlockCollision(Ball& b, Block& p){
	bool collide = false;

	sf::Vector2f paddlePos = p.currentPosition();
	sf::Vector2f ballPos = b.currentPosition();

	sf::Vector2f playerDimn = p.getSize();
	float ballRad = b.getRad();
	
	sf::Color blockColor = p.getColor();
	sf::RectangleShape blockS = sf::RectangleShape(playerDimn);
	sf::RectangleShape ballS = sf::RectangleShape(sf::Vector2f(ballRad, ballRad));

	blockS.setPosition(paddlePos);
	ballS.setPosition(ballPos);

	if(blockS.getGlobalBounds().intersects(ballS.getGlobalBounds())){

		collide = true;	
	//	std::cout<<"collision";
		b.setSpeed(b.getSpeedX(), -b.getSpeedY());
	}

	return collide;
}

bool GameWindow::PaddleBallCollision(Paddle& p, Ball& b){
	bool collide = false;

	sf::Vector2f paddlePos = p.currentPosition();
	sf::Vector2f ballPos = b.currentPosition();

	sf::Vector2f playerDimn = p.getSize();
	float ballRad = b.getRad();
	
	sf::RectangleShape paddleS = sf::RectangleShape(playerDimn);
	sf::RectangleShape ballS = sf::RectangleShape(sf::Vector2f(ballRad, ballRad));

	paddleS.setPosition(paddlePos);
	ballS.setPosition(ballPos);

	if(paddleS.getGlobalBounds().intersects(ballS.getGlobalBounds())){
		collide = true;
	//	std::cout<<"collision";
		b.setSpeed(b.getSpeedX(), -b.getSpeedY());
	}

	return collide;
}

bool GameWindow::BallBelowPaddle(Paddle& p, Ball& b){
	bool collide = false;

	sf::Vector2f paddlePos = p.currentPosition();
	sf::Vector2f ballPos = b.currentPosition();
	
	if(ballPos.y > paddlePos.y){
		 GameOver();
	//	std::cout<<"paddle y: "<<playerLives;
		// Game Over at first touch --> Yes
	//	if(playerLives > 250){
	//		_mainWindow.close();
	//		GameOver();
	//	}
		playerLives++;
	}

	return collide;
}


GameWindow::GameState GameWindow::_gameState = Uninitialized;
sf::RenderWindow GameWindow::_mainWindow;
