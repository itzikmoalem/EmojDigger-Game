#include "Controller.h"

void Controller::Run()
{
	Menu menu;			// Menu kind var.
	DataBar dataBar;	// DataBar kind var.

	auto window = sf::RenderWindow(sf::VideoMode(1920, 1080), "EmojDigger");

	LoadFont(); // Fonts loading
	LoadSounds(); // Sounds loading
	LoadTextures(); // Texture loading

	sf::Sound music;										//Game Music
	music.setBuffer(m_manager.GetSound(S_Game));
	music.setVolume(20);
	music.setLoop(1);

	while (window.isOpen())
	{
		music.stop();

		loadBoardtxt();											//Load levels file	

		if (menu.StartMenu(window, m_manager))				//Bool function for check if "New game" button pressed.
		{
			music.play();									// Playing game music

			m_board.buildBoard(m_file, m_manager, 0, dataBar);		//Build level in board
			dataBar.buildDataBar(window, m_manager);		//Build data bar
			dataBar.databarUpdate();

			dataBar.setStats(3, m_board.getStones());		//Reset stones by the txt file

			m_time.restart();								//Reset to clock

			while (dataBar.getStats(1) > 0)					//While Life > 0
			{
				window.clear();

				if (diamondOver(m_board))					//Check if Diamonds over and level up
				{
					m_file.get();
					if (m_file.peek() == EOF)
					{
						m_win = true;						// If the user wins
						youWin(m_manager, window);			// Showing "You Win" Texture
						break;
					}
					m_board.buildBoard(m_file, m_manager, 0, dataBar);		//Build level in board
					dataBar.databarUpdate();
					dataBar.setStats(3, m_board.getStones());		//Reset stones by the txt file
					m_time.restart();								//Reset to clock
				}

				m_board.printBackground(window);			//Print Background
				m_board.printBoard(window);					//Print Objects

				dataBar.printDataBar(window, m_time);		//Print DataBar

				if (timeOver(dataBar) || stonesOver(dataBar))			//If Time is over || Stones are over
				{
					music.stop();

					if (timeOver(dataBar))								//Text Message Effect
						MessageText(0, m_manager, window);
					else
						MessageText(1, m_manager, window);				// Stone message effect

					m_board.buildBoard(m_file, m_manager, 1, dataBar);		//Build level in board
					dataBar.setStats(1, -1);						//-1 Life
					dataBar.setStats(3, m_board.getStones() + 1);		//Reset stones by the txt file
					m_time.restart();

					music.play();
				}

				m_board.getMove(m_time, dataBar, m_manager, window);			//Get Event from the user

				window.display();
			}

			if (!m_win)									// Game over check
				youLose(m_manager, window);
		}
	}
}

//Load Board
void Controller::loadBoardtxt()
{
	if (m_file.is_open())
		m_file.close();

	m_file.open("Board.txt");		//load levels to m_file

	if (!m_file.is_open())
	{
		std::cerr << "Board.txt cannot be opened!" << std::endl;
	}
}

//Load Textures method
void Controller::LoadTextures()
{
	m_manager.LoadTexture(O_Digger, DIGGER_PNG);
	m_manager.LoadTexture(O_Monster, MONSTER_PNG);
	m_manager.LoadTexture(O_Smart_Mon, SMART_MON_PNG);
	m_manager.LoadTexture(O_Stone, STONE_PNG);
	m_manager.LoadTexture(O_Wall, WALL_PNG);
	m_manager.LoadTexture(O_Diamond, DIAMOND_PNG);
	m_manager.LoadTexture(O_Gift, GIFT_PNG);
	m_manager.LoadTexture(T_Heart, HEART_PNG);
	m_manager.LoadTexture(M_Nostone, NOSTONE_PNG);
	m_manager.LoadTexture(M_Timesup, TIMESUP_PNG);
	m_manager.LoadTexture(M_Youlose, YOULOSE_PNG);
	m_manager.LoadTexture(M_Youwin, YOUWIN_PNG);
	m_manager.LoadTexture(M_Busted, BUSTED_PNG);
	m_manager.LoadTexture(M_Btime, B_TIME_PNG);
	m_manager.LoadTexture(M_Bscore, B_SCORE_PNG);
	m_manager.LoadTexture(M_Bstone, B_STONE_PNG);
}

//Load Font method
void Controller::LoadFont()
{
	m_manager.LoadFont(FONT);
}

//Load Sounds method
void Controller::LoadSounds()
{
	m_manager.LoadSound(S_Game, MUSIC_GAME);
	m_manager.LoadSound(S_Start, MUSIC_START);
	m_manager.LoadSound(S_Message, MUSIC_MESSAGE);
	m_manager.LoadSound(S_Text, MUSIC_TEXT);
}

//Checking if time is Over
bool Controller::timeOver(DataBar &databar)
{
	if (databar.getTimeStart() - (m_time.getElapsedTime().asMilliseconds() / 1000) <= 0)
		return true;

	return false;
}

//Checking if stones is over
bool Controller::stonesOver(DataBar &databar)
{
	if (databar.getStats(3) < 0)
		return true;

	return false;
}

bool Controller::diamondOver(Board& board)
{
	if (board.getDiamonds() <= 0)
		return true;

	return false;
}

//This function print the cause of deacrese 1 heart
void Controller::MessageText(bool op, Manager& manage, sf::RenderWindow &window)
{
	sf::Sprite temp;	//Picture

	if (!op)
		temp.setTexture(manage.GetTexture(M_Timesup)); // Time left case
	else
		temp.setTexture(manage.GetTexture(M_Nostone)); // Stone left case

	sf::Sound sound;								// getting sound
	sound.setBuffer(manage.GetSound(S_Message));
	sound.setVolume(100);
	sound.play();

	float t = PAUSE;

	sf::Clock clock;
	clock.restart().asSeconds();

	while (t > 0)
	{
		window.clear();
		window.draw(temp);
		t -= clock.getElapsedTime().asSeconds();
		window.display();
	}
}
// Winning texture showing function on the screen
void Controller::youWin(Manager& manage, sf::RenderWindow& window)
{
	sf::Sprite temp;	//Picture

	temp.setTexture(manage.GetTexture(M_Youwin)); // You win texture

	sf::Sound sound;
	sound.setBuffer(manage.GetSound(S_Message));
	sound.setVolume(100);
	sound.play();

	float t = PAUSE;

	sf::Clock clock;
	clock.restart().asSeconds();

	while (t > 0)
	{
		window.clear();
		window.draw(temp);
		t -= clock.getElapsedTime().asSeconds();
		window.display();
	}
}
// Losing texture showing function on the screen
void Controller::youLose(Manager& manage, sf::RenderWindow& window)
{
	sf::Sprite temp;	//Picture

	temp.setTexture(manage.GetTexture(M_Youlose));

	sf::Sound sound;
	sound.setBuffer(manage.GetSound(S_Message));
	sound.setVolume(150);
	sound.play();

	float t = PAUSE;

	sf::Clock clock;
	clock.restart().asSeconds();

	while (t > 0)
	{
		window.clear();
		window.draw(temp);
		t -= clock.getElapsedTime().asSeconds();
		window.display();
	}
}
