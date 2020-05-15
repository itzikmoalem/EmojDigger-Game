#pragma once

#include "SFML/Graphics.hpp"
#include "Monster.h"

class SmartMonster : public Monster
{
public:
	SmartMonster(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size);

	void Move(float delta, sf::Vector2f vec) override; // Moving function


private:

	float m_deltaSmartMon;
};