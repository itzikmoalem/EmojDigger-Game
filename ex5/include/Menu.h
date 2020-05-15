#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Vector"
#include "iostream"
#include "string"
#include "Consts.h"
#include "Manager.h"

using std::string;
using std::vector;

class Menu
{
public:
	Menu();
	bool StartMenu(sf::RenderWindow& window, Manager &manager); // Running a few functions to start menu

	void loadBackground(sf::RenderWindow& window); // Loading background
	void loadTexture();								//Loading textures
	void loadTextureName();							//Also ^

	void buildMenu();								//Insert textures into rectangle shapes

	bool runMenu(sf::RenderWindow& window, Manager &manager);			//Running menu function

	bool EventMenu(sf::RenderWindow& window, sf::Event event);		//Event mouse function
	void EffectMenu(sf::RenderWindow& window);		//Effect hover mouse function

	bool newGame();

private:

	vector<sf::RectangleShape> m_menu_rec;
	vector<sf::Texture> m_texture;
	string menu_texture[2];

};