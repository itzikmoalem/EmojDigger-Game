#pragma once

#include <vector>
#include <fstream>
#include "SFML/Graphics.hpp"

#include "Object.h"
#include "Digger.h"
#include "Manager.h"
#include "Consts.h"
#include "Monster.h"
#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "DataBar.h"

using std::vector;
using std::unique_ptr;

class Board
{
public:
	Board();	//constractur - load background  
	~Board();

	void printBackground(sf::RenderWindow& window); // Printing background
	void buildBoard(std::ifstream &file, Manager& manager, bool restart, DataBar& databar); // Building board
	void printBoard(sf::RenderWindow& window);		// Printing board
	void getMove(sf::Clock& time, DataBar &databar, Manager& manager, sf::RenderWindow& window); // Moving function
	void handleCollision(Object& object); // Handle collision function
		
	void sizeVec(); // Resize vectors

	int getStones(); // Getting stones
	int getDiamonds(); // Getting diamonds
	int getRows(); // Getting rows
	int getCols(); // Getting cols

	void RegularMonsterMove(const float delta); // Regular monster moving function
	void SmartMonsterMove(const float delta); // Smart monster moving function

	int getShorterPath(const sf::Vector2f MonsterPos); // Getting shorter path between digger and monster algorithm to the smart monster
	// function checking case that digger and monster collide
	void CheckCollide(DataBar& databar, sf::Clock &time, Manager& manager, sf::RenderWindow &window); 

	void showMessage(Manager& manager, sf::RenderWindow& window);
	void MessageGifts(Manager& manager, sf::RenderWindow& window);
	bool isValidMove(const float x, const float y, sf::RectangleShape mon); // Valid move function

private:

	sf::Sprite m_backGround;	
	sf::Texture m_backGeoundTex;
	
	unique_ptr<Digger> m_Digger;
	vector<vector<unique_ptr<Monster>>> m_Monster;
	vector<vector<unique_ptr<Static>>> m_Unmoveable;	// #0 Walls ,#1 Diamonds ,#2 Stones ,#3 Gifts

	vector<vector<sf::Vector2f>> m_MonsLoc;		//save the location of monster

	int m_Width;	//Size of each Rectangle
	int m_Length;

	int m_Rows;		//Board.txt data
	int m_Cols;
	int m_Stones;
	int m_Time;

	int m_SaveChar;

	int m_oppsite;

	sf::Clock m_timer;
	
};