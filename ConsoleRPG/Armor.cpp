#include"Armor.h"

dArr<std::string> Armor::names;

void Armor::initNames()
{
	Armor::names.push("Bro-Saver");
	Armor::names.push("Cotton-Rag");
	Armor::names.push("Devlish-Defender");
	Armor::names.push("Angels-Balls");
	Armor::names.push("Iron-Sheets");
	Armor::names.push("Assassins-Bedsheets");
}

Armor::Armor()
	:Item()
{
	this->type = -1;
	this->defence = 0;
}

Armor::Armor(int level, int rarity)
	:Item(itemTypes::ARMOR, level, rarity)
{
	this->defence = rand() % (level * (rarity+1));
	this->defence += (rarity + 1) * 5;
	this->type = rand() % 4;
	
	switch (this->type)
	{
	case armorType::HEAD:
		this->typeStr = "Head";
			break;
	case armorType::CHEST:
		this->typeStr = "Chest";
			break;
	case armorType::ARMS:
		this->typeStr = "Arms";
			break;
	case armorType::LEGS:
		this->typeStr = "Legs";
			break;
	default:
		this->typeStr = "ERROR INVALID!";
			break;
	}

	this->setName(Armor::names[rand() % Armor::names.size()]);

	if(rarity == 3)
		this->defence += level * 5;
	else if (rarity == 4)
		this->defence += level * 10;
}

Armor::Armor(int type, int defence, std::string name, int level, int buyValue, int sellValue, int rarity)
	: Item(itemTypes::ARMOR, name, level, buyValue, sellValue, rarity)
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

std::string Armor::toString()const
{
	std::string str = 
		this->getName()
		+ " | Type: "
		+ this->typeStr
		+ " | Lvl: "
		+ std::to_string(this->getLevel())
		+ " | Rarity: "
		+ std::to_string(this->getRarity())
		+ " | Def: "
		+ std::to_string(this->defence);

	return str;
}

std::string Armor::toStringSave()const
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
		+ std::to_string(this->defence)
		+ " "
		+ std::to_string(this->type)
		+ " ";

	return str;
}