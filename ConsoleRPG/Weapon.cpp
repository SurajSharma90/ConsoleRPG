#include"Weapon.h"

dArr<std::string> Weapon::names;

void Weapon::initNames()
{
	Weapon::names.push("Butter-Knife");
	Weapon::names.push("Leaf-Cutter");
	Weapon::names.push("Face-Shredder");
	Weapon::names.push("Bro-Knife");
	Weapon::names.push("Katana-Sword");
	Weapon::names.push("Brutal-Murder");
}

Weapon::Weapon()
	:Item()
{
	this->damageMax = 0;
	this->damageMin = 0;
}

Weapon::Weapon(int level, int rarity)
	:Item(itemTypes::WEAPON, level, rarity)
{
	this->damageMax = rand() % level * (rarity+1);
	this->damageMax += (rarity+1) * 5;
	this->setName(Weapon::names[rand() % Weapon::names.size()]);

	if (rarity == 3)
		this->damageMax += level * 5;
	else if (rarity == 4)
		this->damageMax += level * 10;

	this->damageMin = this->damageMax / 2;
}

Weapon::Weapon(int damageMin, int damageMax, std::string name, int level, int buyValue, int sellValue, int rarity)
	: Item(itemTypes::WEAPON, name, level, buyValue, sellValue, rarity)
{
	this->damageMin = damageMin;
	this->damageMax = damageMax;
}

Weapon::~Weapon()
{

}

Weapon* Weapon::clone()const
{
	return new Weapon(*this);
}

std::string Weapon::toString()const
{
	std::string str =
		this->getName()
		+ " | Lvl: "
		+ std::to_string(this->getLevel())
		+ " | Rarity: "
		+ std::to_string(this->getRarity())
		+ " | Damage: "
		+ std::to_string(this->damageMin)
		+ " - "
		+ std::to_string(this->damageMax);

	return str;
}

std::string Weapon::toStringSave()const
{
	std::string str =
		std::to_string(this->getItemType())
		+ " "
		+ this->getName()
		+ " "
		+ std::to_string(this->getLevel())
		+ " "
		+ std::to_string(this->getRarity())
		+ " "
		+ std::to_string(this->getBuyValue())
		+ " "
		+ std::to_string(this->getSellValue())
		+ " "
		+ std::to_string(this->damageMin)
		+ " "
		+ std::to_string(this->damageMax)
		+ " ";

	return str;
}