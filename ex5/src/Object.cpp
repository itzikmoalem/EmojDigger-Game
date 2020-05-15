#include "Object.h"
#include "Diamond.h"
#include "Digger.h"
#include "Gift.h"
#include "Stone.h"
#include "Wall.h"
#include "Monster.h"
#include "SmartMonster.h"
#include "RegularMonster.h"

#include <iostream>

Object::Object(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: m_Rec({ size.x,size.y }) ,m_isDeleted (false)
{
	m_Rec.setSize(size);
	m_Rec.setTexture(&texture);
	m_Rec.setPosition(pos);
}
// Return object position
sf::Vector2f Object::getPostion()
{
	return sf::Vector2f(m_Rec.getPosition());
}
// Print object function
void Object::printObject(sf::RenderWindow& window)
{
	window.draw(m_Rec);
}
// Return object rec
sf::RectangleShape Object::getRec()
{
	return m_Rec;
}
// Set object position
void Object::setCurrPos(const sf::Vector2f vec)
{
	m_Rec.setPosition(vec);
}
// Collision function
bool Object::checkCollision(const sf::FloatRect& floatRect) const
{
	return true;
}
// Moving function
void Object::Move(sf::Vector2f vec)
{
	m_Rec.move(vec);
}
// Deleting set object
void Object::setDeleted(const bool val)
{
	m_isDeleted = val;
}
// Checking deletion
bool Object::isDeleted()
{
	if (!m_isDeleted)
		return false;
	return true;
}
