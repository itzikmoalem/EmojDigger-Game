#pragma once

#include "SFML/Graphics.hpp"
#include "Static.h"

class Diamond : public Static
{
public:
	Diamond(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size); // Constarctor
	~Diamond() {};																			// Distractor


	// Collision function //
	void HandleCollision(Object& other) override;
	void HandleCollision(Monster& other) override;
	void HandleCollision(Digger& other) override;
	void HandleCollision(Wall& other) override;
	void HandleCollision(Diamond& other) override;
	void HandleCollision(Stone& other) override;
	void HandleCollision(Gift& other) override;

private:

};

