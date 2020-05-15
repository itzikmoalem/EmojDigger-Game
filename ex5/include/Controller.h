#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"
#include "DataBar.h"
#include "Board.h"
#include "Consts.h"
#include <fstream>

using std::ifstream;

class Controller
{
public:
	Controller() {};	//Constarctor

	void Run();			//Main Function

	void loadBoardtxt(); // Loading board txt
	void LoadTextures(); // Loading textures
	void LoadFont();	// Loading font
	void LoadSounds();	// Loading sound

	bool timeOver(DataBar &databar); // Check if time over
	bool stonesOver(DataBar &databar); // Check if stones over
	bool diamondOver(Board& board); // Check if diamond over

	void MessageText(bool op, Manager &manage, sf::RenderWindow& window); // Message text function effect

	void youWin(Manager& manage, sf::RenderWindow& window); // Winning function 
	void youLose(Manager& manage, sf::RenderWindow& window); // Losing function

private:

	sf::Clock m_time;	//Main Clock
	ifstream m_file;	
	Manager m_manager;	
	Board m_board;

	bool m_win = false;
};