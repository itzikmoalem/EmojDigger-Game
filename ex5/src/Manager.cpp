#include "Manager.h"

Manager::Manager()
{
	// Resize the vector texture and sound vector
	m_textures.resize(18);
	m_sounds.resize(9);
}
// Loading texture function
void Manager::LoadTexture(const int &num, const string &name)
{
	m_textures[num].loadFromFile(name);
	m_textures[num].setSmooth(1);
}
// Getting texture function
sf::Texture& Manager::GetTexture(const int& num)
{
	return this->m_textures[num];
}
// Loading sound function
void Manager::LoadSound(const int& num, const string& name)
{
	m_sounds[num].loadFromFile(name);
}
// Getting sound function
sf::SoundBuffer& Manager::GetSound(const int& num)
{
	return this->m_sounds[num];
}
// Loading font function
void Manager::LoadFont(const string& name)
{
	m_font.loadFromFile(name);
}
// Getting font function
sf::Font& Manager::GetFont()
{
	return m_font;
}
