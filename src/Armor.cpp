#include "Armor.h"

std::vector<std::string> Armor::names;

void Armor::initNames()
{
  Armor::names.push_back("Bro-Saver");
  Armor::names.push_back("Cotton-Rag");
  Armor::names.push_back("Devlish-Defender");
  Armor::names.push_back("Angels-Balls");
  Armor::names.push_back("Iron-Sheets");
  Armor::names.push_back("Assassins-Bedsheets");
}

Armor::Armor(int level, int rarity) : Item(ItemTypes::ARMOR, level, rarity)
{
  int denominator = level * (rarity + 1);
  if (denominator == 0)
  {
    // Handle the zero case here, perhaps set to a default value or log an error.
    defense_ = 0;  // or some default value
  }
  else
  {
    defense_ = rand() % denominator;
  }
  defense_ += (rarity + 1) * 5;
  type_ = rand() % 4;

  switch (type_)
  {
    case armorType::HEAD:
      type_str_ = "Head";
      break;
    case armorType::CHEST:
      type_str_ = "Chest";
      break;
    case armorType::ARMS:
      type_str_ = "Arms";
      break;
    case armorType::LEGS:
      type_str_ = "Legs";
      break;
    default:
      type_str_ = "ERROR INVALID!";
      break;
  }

  setName(Armor::names[rand() % Armor::names.size()]);

  if (rarity == 3)
    defense_ += level * 5;
  else if (rarity == 4)
    defense_ += level * 10;
}

Armor::Armor(int type, int defense, std::string name, int level, int buy_value, int sell_value, int rarity)
  : Item(ItemTypes::ARMOR, name, level, buy_value, sell_value, rarity)
{
  type_ = type;
  defense_ = defense;
  switch (type_)
  {
    case armorType::HEAD:
      type_str_ = "Head";
      break;
    case armorType::CHEST:
      type_str_ = "Chest";
      break;
    case armorType::ARMS:
      type_str_ = "Arms";
      break;
    case armorType::LEGS:
      type_str_ = "Legs";
      break;
    default:
      type_str_ = "ERROR INVALID!";
      break;
  }
}

Armor::~Armor()
{
}

std::shared_ptr<Item> Armor::clone() const
{
  return std::static_pointer_cast<Item>(std::make_shared<Armor>(*this));
}

std::string Armor::toString() const
{
  std::string str = getName() + " | Type: " + type_str_ + " | Lvl: " + std::to_string(getLevel()) +
                    " | Rarity: " + std::to_string(getRarity()) + " | Def: " + std::to_string(defense_);

  return str;
}

std::string Armor::toStringSave() const
{
  std::string str = std::to_string(getItemType()) + " " + getName() + " " + std::to_string(getLevel()) + " " +
                    std::to_string(getRarity()) + " " + std::to_string(getBuyValue()) + " " +
                    std::to_string(getSellValue()) + " " + std::to_string(defense_) + " " + std::to_string(type_) + " ";

  return str;
}

int Armor::getDefense() const
{
  return defense_;
}

int Armor::getType() const
{
  return type_;
}