#pragma once

#include "Consts.h"
#include "Character.h"
#include "SFML/Graphics.hpp"

class Monster : public Character
{
public:
	Monster(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size); // constractor

	void setDelta(const float num); // Setting delta function

	// Collision functions //
	void HandleCollision(Object& other) override;
	void HandleCollision(Monster& other) override;
	void HandleCollision(Digger& other) override;
	void HandleCollision(Wall& other) override;
	void HandleCollision(Diamond& other) override;
	void HandleCollision(Stone& other) override;
	void HandleCollision(Gift& other) override;

	bool isBlocked(); // When object need to stop moving
	void setBlock(const bool val); // Stop moving set

	void setRandom(int num); // Setting random move
	int getRandom();		// Getting random move

	void CheckLimitScreen();	// Limit screen check

	void setCollide(const bool val); // Colllide function
	bool getCollide();



private:

	bool m_Collide = false;
	float m_deltaMonster;
	
	bool m_isBlock = true;
	int m_RandomNum = 0;
};