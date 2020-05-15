#include "Character.h"

Character::Character(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Object(texture, pos, size)
{
}

// Board borders valid check
bool Character::isValid(const int l, const int m)
{
	double keepX = m_Rec.getPosition().x;
	double keepY = m_Rec.getPosition().y;

	if ((keepX + l >= X_BOARD-2 && keepX + l <= W_SCREEN - X_BOARD * 1.5) &&
		(keepY + m >= Y_BOARD && keepY + m <= L_SCREEN  )) // The screen board check
		return true;

	return false;
}

// Saving position function
void Character::setPos(const sf::Vector2f vec)
{
	m_savePos = vec;
}
// Getting position function
sf::Vector2f Character::getPos()
{
	return m_savePos;
}
