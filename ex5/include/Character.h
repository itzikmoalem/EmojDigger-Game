#pragma once

#include "Object.h"
#include "Consts.h"
#include "SFML/Graphics.hpp"



class Character : public Object
{
public:
	Character(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size); // Constarctor
	~Character() {};																			// Distractor

	virtual void Move(float delta, sf::Vector2f vec) = 0; // moving function virtual for monsters and digger

	bool isValid(const int l, const int m); // Valid check function
	void setPos(const sf::Vector2f vec); // Setting position function
	sf::Vector2f getPos(); // Getting position function

protected:


private:

	sf::Vector2f m_savePos;

};