#pragma once

#include "Character.h";
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Digger : public Character
{
public:
	Digger(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size); // Constractor
	~Digger() {};																			// Distractor		

	// Collision functions  //
	void HandleCollision(Object& other) override;
	void HandleCollision(Monster& other) override;
	void HandleCollision(Digger& other) override;
	void HandleCollision(Wall& other) override;
	void HandleCollision(Diamond& other) override;
	void HandleCollision(Stone& other) override;
	void HandleCollision(Gift& other) override;

	void Move(float delta, sf::Vector2f vec) override; // Moving function override

	void resetAll(); // Reset stats
	int getLife();	//Get digger life
	int getScore(); // Get digger score
	int getStone(); // Get digger stone left
	int getTime(); // Get time
	int getGiftype();
	void setGiftype(const int num);

private:

	int m_stone =0;
	int m_life =0;
	int m_score =0;
	int m_time = 0;

	float m_delta;

	int m_giftype =0;	//save kind of gift: 0 - no gift, 1 - score, 2 - stone, 3 - time
};