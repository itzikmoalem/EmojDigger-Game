#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "Digger.h"

Stone::Stone(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Static(texture,pos,size)
{
}

void Stone::HandleCollision(Object& other)
{
	other.HandleCollision(*this);
}

void Stone::HandleCollision(Monster& other)
{
}
// Digger eat stone - deleting
void Stone::HandleCollision(Digger& other)
{
	setDeleted(1);
}

void Stone::HandleCollision(Wall& other)
{
}

void Stone::HandleCollision(Diamond& other)
{
}

void Stone::HandleCollision(Stone& other)
{
}

void Stone::HandleCollision(Gift& other)
{
}


