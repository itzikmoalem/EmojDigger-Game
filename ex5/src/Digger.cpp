#include "Digger.h"
#include "Static.h"
#include "Monster.h"
#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "Character.h"
#include "Consts.h"

#include <iostream>
#include <random>

Digger::Digger(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Character(texture, pos, size)
{
}
// Moving digger function
void Digger::Move(float delta, sf::Vector2f vec)
{
	m_delta = delta;

	// Valid moving check
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && isValid(2, 0)) // Right
		m_Rec.move(sf::Vector2f(SPEED * delta, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && isValid(-2, 0)) // Left
		m_Rec.move(sf::Vector2f(-SPEED * delta, 0.0f));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && isValid(0, 2)) // Down
		m_Rec.move(sf::Vector2f(0.0f, SPEED * delta));

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && isValid(0, -2)) // Up
		m_Rec.move(sf::Vector2f(0.0f, -SPEED * delta));
}
// Reset stats
void Digger::resetAll()
{
	m_life = 0;
	m_score = 0; 
	m_stone = 0;
	m_time = 0;
}
// Return the life of the digger
int Digger::getLife()
{
	return m_life;
}
// Return the score of the digger
int Digger::getScore()
{
	return m_score;
}
// Return the stones left of the digger
int Digger::getStone()
{
	return m_stone;
}
// Return the time left
int Digger::getTime()
{
	return m_time;
}
int Digger::getGiftype()
{
	return m_giftype;
}
void Digger::setGiftype(const int num)
{
	m_giftype = num;
}
// Collision //
//-------------------------------------------//
void Digger::HandleCollision(Object& other)
{
	other.HandleCollision(*this);
}
void Digger::HandleCollision(Monster& other)
{
}
void Digger::HandleCollision(Digger& other)
{
}
// Digger collision with wall
void Digger::HandleCollision(Wall& other)
{
	Move(-m_delta, { 0,0 });
}
// Digger eat diamond += score
void Digger::HandleCollision(Diamond& other)
{
	m_score += 15;
}
// Digger eat stone -= stone left
void Digger::HandleCollision(Stone& other)
{
	m_stone -= 1;
}
// Digger eat gift
// Random number that gives Score\Life\Stone

void Digger::HandleCollision(Gift& other)
{
	std::srand(std::time(nullptr));
	int random = std::rand();

	if (random % 2 == 0)
	{
		m_score += 20;
		m_giftype = 1;
	}
	else if (random % 3 == 0 || random % 5 == 0)
	{
		m_stone += 5;
		m_giftype = 2;
	}
	else
	{
		m_time += 15;
		m_giftype = 3;
	}
}
