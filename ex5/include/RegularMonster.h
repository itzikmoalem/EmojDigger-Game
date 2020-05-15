#pragma once

#include "SFML/Graphics.hpp"
#include "Monster.h"

class RegularMonster : public Monster
{
public:
	RegularMonster(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size);

	void Move(float delta, sf::Vector2f vec) override; // Moving function override

	bool isValid(const int l, const int m); // Valid moving check


private:
};