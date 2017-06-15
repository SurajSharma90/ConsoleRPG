#include"Armor.h"

Armor::Armor(int type, int defence, std::string name, int level, int buyValue, int sellValue, int rarity)
	: Item(name, level, buyValue, sellValue, rarity)
{
	this->type = type;
	this->defence = defence;
}

Armor::~Armor()
{

}

Armor* Armor::clone()const
{
	return new Armor(*this);
}

std::string Armor::toString()
{
	std::string str = std::to_string(this->type) + " " + std::to_string(this->defence);

	return str;
}