#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "Digger.h"

SmartMonster::SmartMonster(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Monster(texture, pos, size)
{
}
// Smart monster moving
void SmartMonster::Move(float delta, sf::Vector2f vec)
{
	m_Rec.move(vec);
}

