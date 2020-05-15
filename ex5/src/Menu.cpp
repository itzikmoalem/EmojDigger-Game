#include "Menu.h"

Menu::Menu(){}

bool Menu::StartMenu(sf::RenderWindow& window, Manager &manager)
{
	loadTextureName();		// Texture name function
	loadTexture();			// Load the texture name into sprite
	buildMenu();			// Setting the sprites into rectangle shapes
	return runMenu(window, manager); // Running menu function
}

void Menu::loadTexture()
{
	//Load the textures into texture vector
	for (int i = 0; i < 2; i++)
	{
		sf::Texture objTexture;
		objTexture.loadFromFile(this->menu_texture[i]);
		m_texture.push_back(objTexture);
	}
}

void Menu::loadTextureName()
{
	// Insert the textures into texture vector
	this->menu_texture[0] = "NewGame.png";
	this->menu_texture[1] = "ExitGame.png";
	this->loadTexture();
}

void Menu::buildMenu()
{
	// Insert the buttons into Rectangle Shapes.
	for (int i = 0; i < 2; i++)
	{
		sf::RectangleShape rec;
		rec.setSize(sf::Vector2f(BUTTON_W, BUTTON_L));

		m_menu_rec.push_back(rec);
		m_menu_rec[i].setTexture(&m_texture[i]);
		m_menu_rec[i].setPosition(BUTTON_POS_X,BUTTON_POS_Y +(i * DISTANCE_BUTTONS));
	}
}

bool Menu::runMenu(sf::RenderWindow& window, Manager &manager)
{
	sf::Event event;

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background_start.png"); // Start background texture
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);

	sf::Sound soundmenu;							// Start sound
	soundmenu.setBuffer(manager.GetSound(S_Start));
	soundmenu.setVolume(30);
	soundmenu.play();

	while (window.waitEvent(event))		// Waiting for event "New game" or "Exit game"
	{
		window.clear();
		window.draw(backgroundSprite);

		EffectMenu(window);	// Effect moving buttons

		for (int i = 0; i < 2; i++)
			window.draw(m_menu_rec[i]); // To print  buttons

		if (EventMenu(window, event))			// Waiting for event
		{
			soundmenu.pause();
			window.clear();
			window.display();
			return true;
		}

		window.display();
	}
	return false;
}

bool Menu::EventMenu(sf::RenderWindow& window, sf::Event event)
{
	//This function waiting for mouse event and apply also mouse effect.
	//The options are "New game" Button, or "Exit game" Button.

	//BUTTON POS X = the value x on the screen
	//BUTTON POS Y = the value y on the screen
	//BUTTON W = the width of the button
	//BUTTON L = the length of the button
	//DISTANCE BUTTON = the distance between the buttons
	//BUTTON MOVE EFFECT = value that moves the button when the mouse hover him

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Left click pressed
	{
		if (event.EventType::MouseButtonReleased)
		{
			int x = sf::Mouse::getPosition(window).x; 
			int y = sf::Mouse::getPosition(window).y;

			// New game button pressed
			if (x >= BUTTON_POS_X && x <= (BUTTON_POS_X + BUTTON_W) &&
				y >= BUTTON_POS_Y && y <= BUTTON_POS_Y + BUTTON_L + BUTTON_MOVE_EFFECT)
				return true;	//New Game Pressed
			
			// Exit game button pressed
			if (x >= BUTTON_POS_X && x <= (BUTTON_POS_X + BUTTON_W) &&
				y >= BUTTON_POS_Y+ DISTANCE_BUTTONS && 
				y <= BUTTON_POS_Y + DISTANCE_BUTTONS + BUTTON_L)	//Exit Game Pressed
				window.close();
		}
	}
	return false;
}

void Menu::EffectMenu(sf::RenderWindow& window)
{
	int x = sf::Mouse::getPosition(window).x;
	int y = sf::Mouse::getPosition(window).y;

	//BUTTON POS X = the value x on the screen
	//BUTTON POS Y = the value y on the screen
	//BUTTON W = the width of the button
	//BUTTON L = the length of the button
	//DISTANCE BUTTON = the distance between the buttons
	//BUTTON MOVE EFFECT = value that moves the button when the mouse hover him

	//New game button hover case:
	if (x >= BUTTON_POS_X && x <= (BUTTON_POS_X + BUTTON_W) &&
		y >= BUTTON_POS_Y && y <= (BUTTON_POS_Y + BUTTON_L))
		m_menu_rec[0].setPosition(BUTTON_POS_X, BUTTON_POS_Y + BUTTON_MOVE_EFFECT); // Mouse effect
	else
		m_menu_rec[0].setPosition(BUTTON_POS_X, BUTTON_POS_Y - BUTTON_MOVE_EFFECT); // Mouse effect


	//Exit game button hover case:
	if (x >= BUTTON_POS_X && x <= (BUTTON_POS_X + BUTTON_W) &&
		y >= BUTTON_POS_Y + DISTANCE_BUTTONS && y <= BUTTON_POS_Y + DISTANCE_BUTTONS+BUTTON_L)
		m_menu_rec[1].setPosition(BUTTON_POS_X, BUTTON_POS_Y + DISTANCE_BUTTONS + BUTTON_MOVE_EFFECT); // Mouse effect
	else
		m_menu_rec[1].setPosition(BUTTON_POS_X, BUTTON_POS_Y + DISTANCE_BUTTONS - BUTTON_MOVE_EFFECT); // Mouse effect
}

bool Menu::newGame()
{
	return true;
}

void Menu::loadBackground(sf::RenderWindow &window)
{
	//This function loading the background texture 
	//and printing it on the screen.

	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile("background_start.png");
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	window.draw(backgroundSprite);
}

