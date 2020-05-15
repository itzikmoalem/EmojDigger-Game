#pragma once

#include "SFML/Graphics.hpp"
#include "Static.h"


class Wall : public Static
{
public:
	Wall(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size); // Constartcor
	~Wall() {};																			// Distractor

	// Collision functions //
	void HandleCollision(Object& other) override;
	void HandleCollision(Monster& other) override;
	void HandleCollision(Digger& other) override;
	void HandleCollision(Wall& other) override;
	void HandleCollision(Diamond& other) override;
	void HandleCollision(Stone& other) override;
	void HandleCollision(Gift& other) override;

	/*virtual void collide(Object& other);
	virtual void collide(Wall& other);*/

private:

};