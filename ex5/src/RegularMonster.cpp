#include "RegularMonster.h"
#include "SmartMonster.h"
#include "Wall.h"
#include "Stone.h"
#include "Diamond.h"
#include "Gift.h"
#include "Digger.h"
#include "Consts.h"

#include <random>

RegularMonster::RegularMonster(const sf::Texture& texture, const sf::Vector2f& pos, const sf::Vector2f& size)
	: Monster(texture, pos, size)
{
}
// Regular monster move
void RegularMonster::Move(float delta, sf::Vector2f vec)
{
	m_Rec.move(vec);
}
// Valid moving check
bool RegularMonster::isValid(const int l, const int m)
{
	double keepX = m_Rec.getPosition().x;
	double keepY = m_Rec.getPosition().y;

	if ((keepX + l >= X_BOARD && keepX + l <= W_SCREEN - X_BOARD * 2.2) &&
		(keepY + m >= Y_BOARD && keepY + m <= L_SCREEN - (Y_BOARD / 2)))
		return true;

	return false;
}
