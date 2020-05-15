#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "string"

using std::string;
class Manager
{
public:
	// The class manager mention to be the class that loading the whole textures, sound and font that
	// needed to be used in the game.

	Manager(); // Constractor
	void LoadTexture(const int &num, const string &name ); // Loading texture function
	sf::Texture &GetTexture(const int& num);			// Getting texture function

	void LoadSound(const int& num, const string& name); // Loading sound function
	sf::SoundBuffer& GetSound(const int& num);			// Getting sound function

	void LoadFont(const string& name);				// Loading font function
	sf::Font& GetFont();							// Getting font function
		
private:

	std::vector<sf::Texture> m_textures;
	sf::Font m_font;
	std::vector<sf::SoundBuffer> m_sounds;


};