#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "Digger.h"

Gift::Gift(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Static(texture,pos,size)
{
}

void Gift::HandleCollision(Object& other)
{
	other.HandleCollision(*this);
}

void Gift::HandleCollision(Monster& other)
{
}
// Digger eat gift
void Gift::HandleCollision(Digger& other)
{
	setDeleted(1);
}

void Gift::HandleCollision(Wall& other)
{
}

void Gift::HandleCollision(Diamond& other)
{
}

void Gift::HandleCollision(Stone& other)
{
}

void Gift::HandleCollision(Gift& other)
{
}
