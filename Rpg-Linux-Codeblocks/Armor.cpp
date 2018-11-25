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
	:Item(ARMOR, level, rarity)
{
	this->defence = rand() % (level * (rarity+1));
	this->defence += (rarity + 1) * 5;
	this->type = rand() % 4;

	switch (this->type)
	{
	case HEAD:
		this->typeStr = "Head";
			break;
	case CHEST:
		this->typeStr = "Chest";
			break;
	case ARMS:
		this->typeStr = "Arms";
			break;
	case LEGS:
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
	: Item(ARMOR, name, level, buyValue, sellValue, rarity)
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
    std::stringstream ss;

	ss <<
		this->getName()
		<< " | Type: "
		<< this->typeStr
		<< " | Lvl: "
		<< this->getLevel()
		<< " | Rarity: "
		<< this->getRarity()
		<< " | Def: "
		<< this->defence;

	return ss.str();
}

std::string Armor::toStringSave()const
{
    std::stringstream ss;

	ss <<
		this->getItemType()
		<< " "
		<< this->getName()
		<< " "
		<< this->getLevel()
		<< " "
		<< this->getRarity()
		<< " "
		<< this->getBuyValue()
		<< " "
		<< this->getSellValue()
		<< " "
		<< this->defence
		<< " "
		<< this->type
		<< " ";

	return ss.str();
}
