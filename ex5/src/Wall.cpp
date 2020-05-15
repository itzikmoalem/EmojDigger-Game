#include "Wall.h"


#include <iostream>

Wall::Wall(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Static(texture,pos,size)
{
}

void Wall::HandleCollision(Object& other)
{
	other.HandleCollision(*this);
}

void Wall::HandleCollision(Monster& other)
{
	
}

void Wall::HandleCollision(Digger& other)
{

}

void Wall::HandleCollision(Wall& other)
{
}

void Wall::HandleCollision(Diamond& other)
{
	
}

void Wall::HandleCollision(Stone& other)
{
}

void Wall::HandleCollision(Gift& other)
{
}
