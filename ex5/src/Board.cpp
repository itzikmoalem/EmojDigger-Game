
#include "Board.h"
#include <iostream>
#include <experimental/vector>
#include <ctime>

using std::vector;
using std::string;
using std::cout;
using std::endl;

Board::Board()
{
	//Loading Board background
	m_backGeoundTex.loadFromFile("background.png");

	//Insert the board background into rectangle shape
	m_backGround.setTexture(m_backGeoundTex);
}

Board::~Board()
{
}

void Board::printBackground(sf::RenderWindow& window)
{
	//draw background Board
	window.draw(m_backGround);
}

//Build Board - Read the next level
void Board::buildBoard(std::ifstream& file, Manager& manager, bool restart, DataBar &databar)
{
	if (!restart)
		m_SaveChar = file.tellg();		//Save the location of file
	else
		file.seekg(m_SaveChar);

	if (file.eof())
		file.close();

	string s;
	char c;

	file >> s;
	m_Rows = stoi(s);		//Reset m_Rows

	file >> s;
	m_Cols = stoi(s);		//Reset m_Cols

	file >> s;
	m_Stones = stoi(s);		//Reset m_Stones

	file >> s;
	m_Time = stoi(s);

	file.get(c);

	sizeVec();				//define m_Width, m_Length by the rows&cols
	
	m_Monster.clear();
	m_Unmoveable.clear();

	m_Monster.resize(2);	//two kind of monsters
	m_Unmoveable.resize(4);	//four kind of unmoveables

	m_MonsLoc.resize(2);	//two kind of monsters
	
	file.get(c);
	file.get(c);

	for (int i = 0; i < m_Rows; i++)
	{
		for (int j = 0; j < m_Cols; j++)
		{
			//Calculate Location of the object
			sf::Vector2f currPos = sf::Vector2f(X_BOARD + (j * m_Width), Y_BOARD + (i * m_Length));
			//Size of the object
			sf::Vector2f currSize = sf::Vector2f(m_Width, m_Length);

			switch (c)
			{
				case '/':
				{
					currSize.x -= SPACE;	//Intilaize the digger size to be smaller than other objects
					currSize.y -= SPACE;	// that he could run easly on the board
					
					currPos.x += SPACE / 2;
					currPos.y += SPACE / 2;

					m_Digger = (std::make_unique<Digger>(manager.GetTexture(O_Digger), currPos, currSize));
					m_Digger->setPos(currPos);
					break;
				}
				case '!':
				{
					currSize.x -= SPACE;	//for monster smaller then rest of objects
					currSize.y -= SPACE;

					currPos.x += SPACE / 2;
					currPos.y += SPACE / 2;

					if ((i + j) % 4 != 0)		//Random Choose Monsters
					{
						m_Monster[0].push_back(std::make_unique<RegularMonster> // Regular monster case
							(manager.GetTexture(O_Monster), currPos, currSize));

						m_MonsLoc[0].push_back(currPos);
					}
					else
					{
						m_Monster[1].push_back(std::make_unique<SmartMonster> // Smart monster case
							(manager.GetTexture(O_Smart_Mon), currPos, currSize));

						m_MonsLoc[1].push_back(currPos);
					}

					break;
				}
				case '#': // Wall object case
				{
					m_Unmoveable[0].push_back(std::make_unique<Wall>(manager.GetTexture(O_Wall), currPos, currSize));
					break;
				}
				case 'D': // Diamond object case
				{
					m_Unmoveable[1].push_back(std::make_unique<Diamond>(manager.GetTexture(O_Diamond), currPos, currSize));
					break;
				}
				case '@': // Stone object case
				{
					m_Unmoveable[2].push_back(std::make_unique<Stone>(manager.GetTexture(O_Stone), currPos, currSize));
					break;
				}
				case '+': // Gift object case
				{
					m_Unmoveable[3].push_back(std::make_unique<Gift>(manager.GetTexture(O_Gift), currPos, currSize));
					break;
				}
			}
			file.get(c);
		}
		file.get(c);
	}
	databar.setTimeStart(m_Time);
}

//Print board data
void Board::printBoard(sf::RenderWindow& window)
{
	m_Digger->printObject(window);					//Print Digger

	for (int i = 0; i < m_Unmoveable.size(); i++)	//Print Unmoveables
	{
		for (int j = 0; j < m_Unmoveable[i].size(); j++)
		{
			m_Unmoveable[i][j]->printObject(window);
		}
	}

	for (int i = 0; i < m_Monster[0].size(); i++)	//Print Regular Monsters
		m_Monster[0][i]->printObject(window);

	for (int i = 0; i < m_Monster[1].size(); i++)	//Print Smart Monsters
		m_Monster[1][i]->printObject(window);
}

void Board::getMove(sf::Clock &time, DataBar &databar, Manager &manager, sf::RenderWindow &window)
{
	float delta = m_timer.restart().asSeconds();
	
	m_Digger->Move(delta, {0,0});	//Move Function by time
	handleCollision(*m_Digger);		//Check Collision

	MessageGifts(manager, window);

	RegularMonsterMove(delta);		//Moving Monsters
	SmartMonsterMove(delta);

	CheckCollide(databar, time, manager, window);

	databar.setStats(1, m_Digger->getLife());	//Update databar by move
	databar.setStats(2, m_Digger->getScore());
	databar.setStats(3, m_Digger->getStone());
	databar.setExtraTime(m_Digger->getTime());

	m_Digger->resetAll();						//Reset Update
}

void Board::handleCollision(Object& object)		//Check Collisions
{
	for (int i = 0; i < m_Unmoveable.size(); i++)
	{
		for (int j = 0; j < m_Unmoveable[i].size(); j++)
		{
			//Check Collision by Rectangle
			if (object.getRec().getGlobalBounds().intersects(m_Unmoveable[i][j]->getRec().getGlobalBounds()))
			{
				object.HandleCollision(*(m_Unmoveable[i][j]));	//if The Object Collied Digger
				m_Unmoveable[i][j]->HandleCollision(object);	//if The Digger Collied an Object
			}
		}
	}
	// Loop to check coliisons
	for (int i = 0; i < m_Monster.size(); i++)
	{
		for (int j = 0; j < m_Monster[i].size(); j++)
		{
			//Check Collision by Rectangle
			if (m_Digger->getRec().getGlobalBounds().intersects(m_Monster[i][j]->getRec().getGlobalBounds()))
			{	
				m_Monster[i][j]->HandleCollision(*m_Digger);	//if The Monster Collied Digger
				break;
			}
		}
	}
	// Loop to erase objects
	for (int i = 0; i < m_Unmoveable.size(); i++)
	{
		for (int j = 0; j < m_Unmoveable[i].size(); j++)
		{
			if (m_Unmoveable[i][j]->isDeleted())
				std::experimental::erase(m_Unmoveable[i], m_Unmoveable[i][j]);	//erase object
		}
	}
}

//Calculate size of a RectangleShape
void Board::sizeVec()
{
	m_Width = W_SCREEN / m_Cols;
	m_Length = L_SCREEN / m_Rows;
}
// Get stone number function
int Board::getStones()
{
	return m_Stones;
}
// Get diamond number function
int Board::getDiamonds()
{
	return m_Unmoveable[1].size();		//diamonds
}
// Get rows of the board
int Board::getRows()
{
	return m_Rows;
}
// Get cold of the board
int Board::getCols()
{
	return m_Cols;
}

//Regular Monster Move
void Board::RegularMonsterMove(const float delta)
{
	std::srand(std::time(nullptr));
	int temp = std::rand();
	
	for (int j = 0; j < m_Monster[0].size(); j++)
	{
		m_Monster[0][j]->CheckLimitScreen();		//Check Position with screen size

		if (m_Monster[0][j]->isBlocked())			//if the monster blocked 
		{
			m_Monster[0][j]->setRandom(temp % 4);		//change deirction
			m_Monster[0][j]->setBlock(0);
		}
		else {

			switch (m_Monster[0][j]->getRandom())
			{
			case 0:
			{
				if (!isValidMove(0, SPEED_MONSTER * delta, m_Monster[0][j]->getRec()))
				{
					m_Monster[0][j]->setBlock(1);
					break;
				}
				m_Monster[0][j]->Move(delta, { 0,SPEED_MONSTER * delta });		//go Up
				break;
			}
			case 1:
			{
				if (!isValidMove(0, -SPEED_MONSTER * delta, m_Monster[0][j]->getRec()))
				{
					m_Monster[0][j]->setBlock(1);
					break;
				}
				m_Monster[0][j]->Move(delta, { 0,-SPEED_MONSTER * delta });		//go Down
				break;
			}
			case 2:
			{
				if (!isValidMove(SPEED_MONSTER * delta, 0, m_Monster[0][j]->getRec()))
				{
					m_Monster[0][j]->setBlock(1);
					break;
				}
				m_Monster[0][j]->Move(delta, { SPEED_MONSTER * delta,0 });		//go Rigth
				break;
			}
			case 3:
			{
				if (!isValidMove(-SPEED_MONSTER * delta, 0, m_Monster[0][j]->getRec()))
				{
					m_Monster[0][j]->setBlock(1);
					break;
				}
				m_Monster[0][j]->Move(delta, { -SPEED_MONSTER * delta,0 });		//go Left
				break;
			}
			}
			handleCollision(*m_Monster[0][j]);		//Check Colliosion
		}
	}
}

//Smart Monster Move
void Board::SmartMonsterMove(const float delta)
{
	for (int j = 0; j < m_Monster[1].size(); j++)
	{
		m_Monster[1][j]->CheckLimitScreen();		//Check Position with screen size

		if (m_Monster[1][j]->isBlocked())			//if the monster blocked 
		{
			m_Monster[1][j]->setRandom((m_Monster[1][j]->getRandom() - 1) % 4);
			m_Monster[1][j]->setBlock(0);
		}
		else
		{
			m_Monster[1][j]->setRandom(getShorterPath(m_Monster[1][j]->getPostion()));
		}

		if (!m_Monster[1][j]->isBlocked())
		{
			switch (m_Monster[1][j]->getRandom())
			{
			case 0:
			{
				if (isValidMove(0, SPEED_MONSTER * delta, m_Monster[1][j]->getRec()))
					m_Monster[1][j]->Move(delta, { 0,SPEED_MONSTER * delta });		//go Up
				break;
			}
			case 1:
			{
				if (isValidMove(0, -SPEED_MONSTER * delta, m_Monster[1][j]->getRec()))
					m_Monster[1][j]->Move(delta, { 0,-SPEED_MONSTER * delta });		//go Down
				break;
			}
			case 2:
			{
				if (isValidMove( SPEED_MONSTER * delta, 0, m_Monster[1][j]->getRec()))
					m_Monster[1][j]->Move(delta, { SPEED_MONSTER * delta,0 });		//go Rigth
				break;
			}
			case 3:
			{
				if (isValidMove(-SPEED_MONSTER * delta, 0, m_Monster[1][j]->getRec()))
					m_Monster[1][j]->Move(delta, { -SPEED_MONSTER * delta,0 });		//go Left
				break;
			}
			}
			handleCollision(*m_Monster[1][j]);		//Check Colliosion
		}
	}
}

//Algorithem of Smart Monster
int Board::getShorterPath(const sf::Vector2f MonsterPos)
{
	const sf::Vector2f DiggerPos = m_Digger->getPostion();

	int direction = 0;
	int max = 0;
	int temp = 0;

	if (DiggerPos.x > MonsterPos.x)		//to right
	{
		temp = DiggerPos.x - MonsterPos.x;
		if (temp > max)
		{
			max = temp;
			direction = 2;
		}
	}
	if (DiggerPos.x <= MonsterPos.x)		//to left
	{
		temp = MonsterPos.x - DiggerPos.x;
		if (temp > max)
		{
			max = temp;
			direction = 3;
		}
	}
	if (DiggerPos.y > MonsterPos.y)		//to up
	{
		temp = DiggerPos.y - MonsterPos.y;
		if (temp > max)
		{
			max = temp;
			direction = 0;
		}
	}
	if (DiggerPos.y <= MonsterPos.y)		//to down
	{
		temp = MonsterPos.y - DiggerPos.y;
		if (temp > max)
		{
			max = temp;
			direction = 1;
		}
	}
	return direction; // The direction for moving
}
//Check collision with monsters function
void Board::CheckCollide(DataBar& databar, sf::Clock &time, Manager& manager, sf::RenderWindow& window)
{
	for (int i = 0; i < m_Monster.size(); i++)			//Runing on Monster Vector
	{
		for (int j = 0; j < m_Monster[i].size(); j++)
		{
			if (m_Monster[i][j]->getCollide())						//Digger collaide monster
			{
				m_Monster[i][j]->setCurrPos(m_MonsLoc[i][j]);	//start position of monsters

				showMessage(manager,window);

				m_Digger->setCurrPos(m_Digger->getPos());			//start position of digger

				time.restart();
				databar.setStats(1, -1);	// -1 Life
			}
		}
	}

	for (int i = 0; i < m_Monster.size(); i++)			//Runing on Monster Vector
		for (int j = 0; j < m_Monster[i].size(); j++)
			m_Monster[i][j]->setCollide(0);				//Return Collide = false
}

void Board::showMessage(Manager& manager, sf::RenderWindow& window)
{
	sf::Sprite temp;	//Picture

	temp.setTexture(manager.GetTexture(M_Busted)); // Time left case

	sf::Sound sound;								// getting sound
	sound.setBuffer(manager.GetSound(S_Message));
	sound.setVolume(100);
	sound.play();

	float pause = PAUSE;

	sf::Clock clock;
	clock.restart().asSeconds();

	while (pause > 0)
	{
		window.clear();
		window.draw(temp);
		pause -= clock.getElapsedTime().asSeconds();
		window.display();
	}
}

//This Function Print Message of the Gift Prize
void Board::MessageGifts(Manager& manager, sf::RenderWindow& window)
{
	int num = m_Digger->getGiftype();

	if (num == 0)		//no gift taken
		return;
	else
	{
		sf::RectangleShape temp;	//Picture

		if (num == 1)
			temp.setTexture(&manager.GetTexture(M_Bscore)); // Score Bonus png
		else if (num == 2)
			temp.setTexture(&manager.GetTexture(M_Bstone)); // Stone Bonus png
		else
			temp.setTexture(&manager.GetTexture(M_Btime)); // Time Bonus png

		temp.setSize(sf::Vector2f(350, 90));
		temp.setPosition(785, Y_BOARD);

		sf::Sound sound;								// getting sound
		sound.setBuffer(manager.GetSound(S_Text));
		sound.setVolume(100);
		sound.play();

		float pause = PAUSE_GIFT;

		sf::Clock clock;
		clock.restart().asSeconds();

		while (pause > 0)
		{
			window.draw(temp);
			pause -= clock.getElapsedTime().asSeconds();
			window.display();
		}
	
		m_Digger->setGiftype(0);
	}
}

// Check if the moving of the monster is valid
bool Board::isValidMove(const float x, const float y, sf::RectangleShape mon)
{
	mon.setPosition(sf::Vector2f(mon.getPosition().x + x, mon.getPosition().y + y));

	for (int i = 0; i < m_Unmoveable[0].size(); i++) // Collision with static objects
	{
		if (mon.getGlobalBounds().intersects(m_Unmoveable[0][i]->getRec().getGlobalBounds()))
			return false;
	}
	
	for (int i = 0; i < m_Unmoveable[2].size(); i++) // Collision with static objects
	{
		if (mon.getGlobalBounds().intersects(m_Unmoveable[2][i]->getRec().getGlobalBounds()))
			return false;
	}
	return true;
}

