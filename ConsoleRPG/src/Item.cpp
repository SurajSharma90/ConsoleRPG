#include "Item.h"

Item::Item(int item_type, int level, int rarity)
{
  name_ = "RANDOM";
  level_ = rand() % (level + 2) + 1;
  rarity_ = rarity;
  buy_value_ = (level_ + rarity_) + level_ * rarity_ * 10;
  sell_value_ = buy_value_ / 2;
  item_type_ = item_type;
}

Item::Item(int item_type, std::string name, int level, int buy_value, int sell_value, int rarity)
{
  item_type_ = item_type;
  name_ = name;
  level_ = level;
  buy_value_ = buy_value;
  sell_value_ = sell_value;
  rarity_ = rarity;
}

Item::~Item()
{
}

std::string Item::debugPrint() const
{
  return name_;
}

const std::string& Item::getName() const
{
  return name_;
}
const int& Item::getLevel() const
{
  return level_;
}
const int& Item::getBuyValue() const
{
  return buy_value_;
}
const int& Item::getSellValue() const
{
  return sell_value_;
}
const int& Item::getRarity() const
{
  return rarity_;
}
const int& Item::getItemType() const
{
  return item_type_;
}

void Item::setName(std::string name)
{
  name_ = name;
}