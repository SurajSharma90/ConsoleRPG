#include "Weapon.h"

std::vector<std::string> Weapon::names;

void Weapon::initNames()
{
  Weapon::names.push_back("Butter-Knife");
  Weapon::names.push_back("Leaf-Cutter");
  Weapon::names.push_back("Face-Shredder");
  Weapon::names.push_back("Bro-Knife");
  Weapon::names.push_back("Katana-Sword");
  Weapon::names.push_back("Brutal-Murder");
}

Weapon::Weapon(int level, int rarity) : Item(ItemTypes::WEAPON, level, rarity)
{
  damage_max_ = rand() % level * (rarity + 1);
  damage_max_ += (rarity + 1) * 5;
  setName(Weapon::names[rand() % Weapon::names.size()]);

  if (rarity == 3)
    damage_max_ += level * 5;
  else if (rarity == 4)
    damage_max_ += level * 10;

  damage_min_ = damage_max_ / 2;
}

Weapon::Weapon(int damage_min, int damage_max, std::string name, int level, int buy_value, int sell_value, int rarity)
  : Item(ItemTypes::WEAPON, name, level, buy_value, sell_value, rarity)
{
  damage_min_ = damage_min;
  damage_max_ = damage_max;
}

Weapon::~Weapon()
{
}

std::shared_ptr<Item> Weapon::clone() const
{
  return std::static_pointer_cast<Item>(std::make_shared<Weapon>(*this));
}

std::string Weapon::toString() const
{
  std::string str = getName() + " | Lvl: " + std::to_string(getLevel()) + " | Rarity: " + std::to_string(getRarity()) +
                    " | Damage: " + std::to_string(damage_min_) + " - " + std::to_string(damage_max_);

  return str;
}

std::string Weapon::toStringSave() const
{
  std::string str = std::to_string(getItemType()) + " " + getName() + " " + std::to_string(getLevel()) + " " +
                    std::to_string(getRarity()) + " " + std::to_string(getBuyValue()) + " " +
                    std::to_string(getSellValue()) + " " + std::to_string(damage_min_) + " " +
                    std::to_string(damage_max_) + " ";

  return str;
}