#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "Digger.h"
#include "..\include\Diamond.h"

Diamond::Diamond(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Static(texture,pos,size)
{
}

void Diamond::HandleCollision(Object& other)
{
	other.HandleCollision(*this);
}

void Diamond::HandleCollision(Monster& other)
{
}
// Digger eat diamond
void Diamond::HandleCollision(Digger& other)
{
	setDeleted(1);
}

void Diamond::HandleCollision(Wall& other)
{
}

void Diamond::HandleCollision(Diamond& other)
{
}

void Diamond::HandleCollision(Stone& other)
{
}

void Diamond::HandleCollision(Gift& other)
{
}
