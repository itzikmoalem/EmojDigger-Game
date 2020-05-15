#pragma once

#include "SFML/Graphics.hpp"

class Digger;
class Monster;
class Wall;
class Diamond;
class Stone;
class Gift;

class Object
{
public:
	Object(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size);

	sf::Vector2f getPostion(); // Getting position object
	
	void printObject(sf::RenderWindow &window); // Printing object

	sf::RectangleShape getRec(); // Getting rectangle shape object

	void setCurrPos(const sf::Vector2f vec); // Setting current position

	bool checkCollision(const sf::FloatRect& floatRect) const; // Collision check

	// Collision Functions //
	virtual void HandleCollision(Object& other) = 0;
	virtual void HandleCollision(Monster& other) = 0;
	virtual void HandleCollision(Digger& other) = 0;
	virtual void HandleCollision(Wall& other) = 0;
	virtual void HandleCollision(Diamond& other) = 0;
	virtual void HandleCollision(Stone& other) = 0;
	virtual void HandleCollision(Gift& other) = 0;

	void Move(sf::Vector2f vec); // Moving function

	void setDeleted(const bool val); // Delete object
	bool isDeleted();					// Deletion check


protected:

	sf::RectangleShape m_Rec;
	bool m_isDeleted;

private:

	sf::Vector2f m_Pose;
};