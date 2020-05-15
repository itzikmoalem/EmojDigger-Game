#include "DataBar.h"

using std::string;
using std::stringstream;

DataBar::DataBar() {}

void DataBar::buildDataBar(sf::RenderWindow& window, Manager &manager)
{
	//reset stats
	buildStats();

	//Loading Data bar background
	m_TexdataBar.loadFromFile("databar.png");

	//Insert the data bar background into rectangle shape
	m_dataBar.setSize(sf::Vector2f(1910, 60));
	m_dataBar.setTexture(&m_TexdataBar);

	//Define sf::Text
	m_text.setCharacterSize(30); // Size of text
	m_text.setFont(manager.GetFont()); // Set the arial font
	m_text.setFillColor(sf::Color::Black); // Color
	m_text.setStyle(sf::Text::Bold); // Bold text

	//Define heart
	m_heart.setTexture(&manager.GetTexture(T_Heart));
	m_heart.setSize(sf::Vector2f(40, 37));

}
void DataBar::printDataBar(sf::RenderWindow& window, sf::Clock time)
{
	//Draw data bar background
	window.draw(m_dataBar);

	//Define sting for draw clock
	stringstream timer;

	if (isTime)
	{
		timer << m_TimeLevel - (time.getElapsedTime().asMilliseconds() / 1000);
		m_text.setString(timer.str());
		m_text.setPosition(1760, 10);
	}

	window.draw(m_text);	//draw clock first

	for (int i = 0; i < 4; i++)		//Print stats
	{
		if (i != 1)
		{
			if (i == 2)	//priavte case of score - for desigin only
				m_text.setPosition(170 + (i * 380), 10);
			else
				m_text.setPosition(242 + (i * 380), 10); // Position on the screen
			m_text.setString(getStatsinString(i)); // Getting the string from the func 
			window.draw(m_text); // draw the text
		}
		else				
		{
			for (int j = 0; j < m_stats[i]; j++)	//heart emoji draw
			{
				m_heart.setPosition(505 + (j * 45), 10);
				window.draw(m_heart);
			}
		}
	}
}

void DataBar::databarUpdate()
{
	m_stats[0]++;		//Level up
	m_stats[3] = 0;		//reset stones
}

void DataBar::setLife(const int num)
{
	m_stats[1] += num;
}

string DataBar::getStatsinString(const int i)
{
	// This function define a stringstream variable
	// that getting the stats[i] value
	// holding that in string
	// and return it to the stat variable (sf::Text that we define above)

	stringstream statHolder;
	statHolder << getStats(i);
	return statHolder.str();
}
void DataBar::buildStats()		//Build stats function (level,life,score,stones)
{
	//Insert values into the array

	m_stats[0] = 0; // Level
	m_stats[1] = LIFE_START; // Life
	m_stats[2] = 0; // Score
	m_stats[3] = 0; // Stones left
}

int DataBar::getStats(const int i)
{
	// Return the stats[i]
	return m_stats[i];
}
// Setting stats
void DataBar::setStats(const int cell, const int num)
{
	m_stats[cell] += num;
}
// Getting start time clock
int DataBar::getTimeStart()
{
	return m_TimeLevel;
}
void DataBar::setTimeStart(const int num)
{
	if (num == -1)
	{
		m_TimeLevel = NOTIME;
		isTime = false;
	}
	else
	{
		m_TimeLevel = num;
		isTime = true;
	}
}
// Setting extra time function when getting a gift
void DataBar::setExtraTime(const int num)
{
	m_TimeLevel += num;
}
