#include "Item.h"

Item::Item()
{
	this->itemType = -1;
	this->name = "EMPTY";
	this->level = 0;
	this->buyValue = 0;
	this->sellValue = 0;
	this->rarity = -1;
}

Item::Item(int itemType, int level, int rarity)
{
	this->name = "RANDOM";
	this->level = rand() % (level+2) + 1;
	this->rarity = rarity;
	this->buyValue = (this->level + this->rarity) + this->level*this->rarity*10;
	this->sellValue = this->buyValue / 2;
	this->itemType = itemType;
}

Item::Item(int itemType, std::string name, int level, int buyValue, int sellValue, int rarity)
{
	this->itemType = itemType;
	this->name = name;
	this->level = level;
	this->buyValue = buyValue;
	this->sellValue = sellValue;
	this->rarity = rarity;
}

Item::~Item()
{

}
