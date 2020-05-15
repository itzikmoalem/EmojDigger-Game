#pragma once
#include "SFML/Graphics.hpp"
#include "Consts.h"
#include "Manager.h"
#include <string>
#include <sstream>

using std::string;

class DataBar
{
public:

	DataBar(); // Constructor

	void buildDataBar(sf::RenderWindow& window, Manager &manager);	// Load Texturs the data bar
	void buildStats();												// Insert values into array
	void printDataBar(sf::RenderWindow& window, sf::Clock time);	//Print the data bar
	void databarUpdate();
	void setLife(const int num);									//Change Life

	string getStatsinString(const int i);							// Getting values from array to string
	int getStats(const int i);										// Getting the stats[i]
	void setStats(const int cell, const int num);

	int getTimeStart();
	void setTimeStart(const int num);
	void setExtraTime(const int num);


private:

	int m_stats[4];			//save Stats
	int m_TimeLevel;

	sf::RectangleShape m_heart;		//Heart for life
	sf::Texture m_Texheart;

	sf::RectangleShape m_dataBar;	//databar rectangle
	sf::Texture m_TexdataBar;

	sf::Text m_text;	//print sync stats

	bool isTime =true;

};