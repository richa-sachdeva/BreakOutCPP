// BreakOut.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

void InitWindow(bool b){
	GameWindow gw = GameWindow();
	sf::RenderWindow& win = gw.GetWindow();

    gw.Start(b);
}

void StartGame(bool b)
{
	//std::cout<<"inside startGame fn \n";
	InitWindow(b);
}


int main(int argc, char* argv[])
{
	
	 
	std::string s, d;
	std::cout << "press d for debug more -> it means player will not die..!";
	std::cin>>d;
	std::cout<<"press y to start the game";
	std::cin>>s;

	bool debug = false;;
	if(d=="d")
		debug = true;
	if(s=="y")
		StartGame(debug);

	return 0;
}

