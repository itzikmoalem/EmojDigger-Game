#include "Monster.h"

#include <iostream>

Monster::Monster(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Character(texture, pos, size)
{
}
// Setting delta monster moving
void Monster::setDelta(const float num)
{
	m_deltaMonster = num;
}

void Monster::HandleCollision(Object& other)
{
	other.HandleCollision(*this);
}

void Monster::HandleCollision(Monster& other)
{
}
// Monster collide digger
void Monster::HandleCollision(Digger& other)
{
	m_Collide = true;
}
// Monster collide wall
void Monster::HandleCollision(Wall& other)
{
	m_isBlock = true;
}

void Monster::HandleCollision(Diamond& other)
{
}
// Monster collide stone
void Monster::HandleCollision(Stone& other)
{
	m_isBlock = true;
}

void Monster::HandleCollision(Gift& other)
{
}
// Blocking monster when try to moving into wall or stones
bool Monster::isBlocked()
{
	return m_isBlock;
}
// Setting block function
void Monster::setBlock(const bool val)
{
	m_isBlock = val;
}
// Setting random moving function to the monster
void Monster::setRandom(int num)
{
	m_RandomNum = num;
}
// Getting random function
int Monster::getRandom()
{
	return m_RandomNum;
}
// Checking valid moving screen
void Monster::CheckLimitScreen()
{
	double keepX = m_Rec.getPosition().x;
	double keepY = m_Rec.getPosition().y;

	if (keepX - 0.1 <= X_BOARD || keepX + 0.1 >= W_SCREEN - X_BOARD * 1.5 ||
		keepY - 0.1 <= Y_BOARD || keepY + 0.1 >= L_SCREEN)
		m_isBlock = true;

}
// Setting collide monster
void Monster::setCollide(const bool val)
{
	m_Collide = val;
}
// Getting collide monster
bool Monster::getCollide()
{
	return m_Collide;
}

