#pragma once

#include "Object.h"
#include "SFML/Graphics.hpp"

class Static : public Object
{
public:
	Static(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size); // Constartcor
	~Static() {};																			// Distractor

protected:

private:

};