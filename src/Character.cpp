#include "Character.h"

Character::Character()
  : weapon_(1, 0)
  , armor_arms_(2, 0, "Initial Gloves", 1, 0, 0, 0)
  , armor_chest_(1, 0, "Initial Shirt", 1, 0, 0, 0)
  , armor_head_(0, 0, "Initial Helmet", 1, 0, 0, 0)
  , armor_legs_(3, 0, "Initial Pants", 1, 0, 0, 0)
{
  distance_traveled_ = 0;

  gold_ = 0;

  name_ = "";
  level_ = 0;
  exp_ = 0;
  expNext_ = 0;

  strength_ = 0;
  vitality_ = 0;
  dexterity_ = 0;
  intelligence_ = 0;

  hp_ = 0;
  hp_max_ = 0;
  stamina_ = 0;
  staminaMax_ = 0;
  damage_min_ = 0;
  damage_max_ = 0;
  defense_ = 0;
  accuracy_ = 0;
  luck_ = 0;

  stat_points_ = 0;
}

Character::Character(std::string name, int distance_traveled, int gold, int level, int exp, int strength, int vitality,
                     int dexterity, int intelligence, int hp, int stamina, int statPoints)
  : weapon_(1, 0)
  , armor_arms_(2, 0, "Initial Gloves", 1, 0, 0, 0)
  , armor_chest_(1, 0, "Initial Shirt", 1, 0, 0, 0)
  , armor_head_(0, 0, "Initial Helmet", 1, 0, 0, 0)
  , armor_legs_(3, 0, "Initial Pants", 1, 0, 0, 0)
{
  distance_traveled_ = distance_traveled;

  gold_ = gold;

  name_ = name;
  level_ = level;
  exp_ = exp;
  expNext_ = 0;

  strength_ = strength;
  vitality_ = vitality;
  dexterity_ = dexterity;
  intelligence_ = intelligence;

  hp_ = hp;
  hp_max_ = 0;
  stamina_ = stamina;
  staminaMax_ = 0;
  damage_min_ = 0;
  damage_max_ = 0;
  defense_ = 0;
  accuracy_ = 0;
  luck_ = 0;

  stat_points_ = statPoints;

  updateStats();
}

Character::~Character()
{
}

// Functions
void Character::initialize(const std::string name)
{
  distance_traveled_ = 0;

  gold_ = 100;

  name_ = name;
  level_ = 1;
  exp_ = 0;

  strength_ = 5;
  vitality_ = 5;
  dexterity_ = 5;
  intelligence_ = 5;

  stat_points_ = 0;

  updateStats();
}

void Character::printStats() const
{
  std::cout << "= Character Sheet ="
            << "\n";
  std::cout << "= Name: " << name_ << "\n";
  std::cout << "= Level: " << level_ << "\n";
  std::cout << "= Exp: " << exp_ << "\n";
  std::cout << "= Exp to next level: " << expNext_ << "\n";
  std::cout << "= Statpoints: " << stat_points_ << "\n";
  std::cout << "\n";
  std::cout << "= Strenght: " << strength_ << "\n";
  std::cout << "= Vitality: " << vitality_ << "\n";
  std::cout << "= Dexterity: " << dexterity_ << "\n";
  std::cout << "= Intelligence: " << intelligence_ << "\n";
  std::cout << "\n";
  std::cout << "= HP: " << hp_ << " / " << hp_max_ << "\n";
  std::cout << "= Stamina: " << stamina_ << " / " << staminaMax_ << "\n";
  std::cout << "= Damage: " << damage_min_ << "( +" << weapon_.getDamageMin() << ")"
            << " - " << damage_max_ << "( +" << weapon_.getDamageMax() << ")"
            << "\n";
  std::cout << "= Defense: " << defense_ << "( +" << std::to_string(getAddedDefense()) << ")"
            << "\n";
  std::cout << "= Accuracy: " << accuracy_ << "\n";
  std::cout << "= Luck: " << luck_ << "\n";
  std::cout << "\n";
  std::cout << "= Distance Traveled: " << distance_traveled_ << "\n";
  std::cout << "= Gold: " << gold_ << "\n";
  std::cout << "\n";
  std::cout << "= Weapon: " << weapon_.getName() << " Lvl: " << weapon_.getLevel() << " Dam: " << weapon_.getDamageMin()
            << " - " << weapon_.getDamageMax() << "\n";
  std::cout << "= Armor Head: " << armor_head_.getName() << " Lvl: " << armor_head_.getLevel()
            << " Def: " << armor_head_.getDefense() << "\n";
  std::cout << "= Armor Chest: " << armor_chest_.getName() << " Lvl: " << armor_chest_.getLevel()
            << " Def: " << armor_chest_.getDefense() << "\n";
  std::cout << "= Armor Arms: " << armor_arms_.getName() << " Lvl: " << armor_arms_.getLevel()
            << " Def: " << armor_arms_.getDefense() << "\n";
  std::cout << "= Armor Legs: " << armor_legs_.getName() << " Lvl: " << armor_legs_.getLevel()
            << " Def: " << armor_legs_.getDefense() << "\n"
            << "\n";
}

std::string Character::getAsString() const
{
  return name_ + " " + std::to_string(distance_traveled_) + " " + std::to_string(gold_) + " " + std::to_string(level_) +
         " " + std::to_string(exp_) + " " + std::to_string(strength_) + " " + std::to_string(vitality_) + " " +
         std::to_string(dexterity_) + " " + std::to_string(intelligence_) + " " + std::to_string(hp_) + " " +
         std::to_string(stamina_) + " " + std::to_string(stat_points_) + " " + weapon_.toStringSave() +
         armor_head_.toStringSave() + armor_chest_.toStringSave() + armor_arms_.toStringSave() +
         armor_legs_.toStringSave();
}

std::string Character::getInvAsString(bool shop)
{
  std::string inv;

  for (size_t i = 0; i < inventory_.size(); i++)
  {
    if (shop)
    {
      inv += std::to_string(i) + ": " + inventory_[i]->toString() + "\n" +
             " - Sell value: " + std::to_string(inventory_[i]->getSellValue()) + "\n";
    }
    else
    {
      inv += std::to_string(i) + ": " + inventory_[i]->toString() + "\n";
    }
  }

  return inv;
}

std::string Character::getInvAsStringSave()
{
  std::string inv;

  for (size_t i = 0; i < inventory_.size(); i++)
  {
    if (inventory_[i]->getItemType() == ItemTypes::WEAPON)
      inv += inventory_[i]->toStringSave();
  }

  inv += "\n";

  for (size_t i = 0; i < inventory_.size(); i++)
  {
    if (inventory_[i]->getItemType() == ItemTypes::ARMOR)
      inv += inventory_[i]->toStringSave();
  }

  return inv;
}

void Character::levelUp()
{
  if (exp_ >= expNext_)
  {
    exp_ -= expNext_;
    level_++;
    expNext_ = static_cast<int>((50 / 3) * ((pow(level_, 3) - 6 * pow(level_, 2)) + 17 * level_ - 12)) + 100;

    stat_points_++;

    updateStats();

    std::cout << "YOU ARE NOW LEVEL " << level_ << "!"
              << "\n\n";
  }
  else
  {
    std::cout << "NOT ENOUGH EXP!"
              << "\n\n";
  }
}

void Character::updateStats()
{
  expNext_ = static_cast<int>((50 / 3) * ((pow(level_, 3) - 6 * pow(level_, 2)) + 17 * level_ - 12)) + 100;

  hp_max_ = (vitality_ * 5) + (strength_) + level_ * 5;
  staminaMax_ = vitality_ + (strength_ / 2) + (dexterity_ / 3);
  stamina_ = staminaMax_;
  damage_min_ = strength_;
  damage_max_ = strength_ + 2;
  defense_ = dexterity_ + (intelligence_ / 2);
  accuracy_ = (dexterity_ / 2) + intelligence_;
  luck_ = intelligence_;

  hp_ = hp_max_;
}

void Character::addToStat(int stat, int value)
{
  if (stat_points_ < value)
    std::cout << "ERROR! NOT ENOUGH STATPOINTS!"
              << "\n";
  else
  {
    switch (stat)
    {
      case 0:
        strength_ += value;
        std::cout << "STRENGTH INCREASED!"
                  << "\n";

        break;

      case 1:
        vitality_ += value;
        std::cout << "VITALITY INCREASED!"
                  << "\n";
        break;

      case 2:
        dexterity_ += value;
        std::cout << "DEXTERITY INCREASED!"
                  << "\n";
        break;

      case 3:
        intelligence_ += value;
        std::cout << "INTELLIGENCE INCREASED!"
                  << "\n";
        break;

      default:
        std::cout << "NO SUCH STAT!"
                  << "\n";
        break;
    }

    stat_points_ -= value;

    updateStats();
  }
}

void Character::equipItem(unsigned index)
{
  if (index < 0 || index >= inventory_.size())
  {
    std::cout << "No valid item selected!"
              << "\n\n";

    return;
  }

  std::shared_ptr<Weapon> w = std::dynamic_pointer_cast<Weapon>(inventory_[index]);
  std::shared_ptr<Armor> a = std::dynamic_pointer_cast<Armor>(inventory_[index]);

  // Is weapon
  if (w)
  {
    if (weapon_.getRarity() >= 0)
      inventory_.addItem(weapon_);  // You might need a way to convert Weapon to shared_ptr<Item> here
    weapon_ = *w;
    inventory_.removeItem(index);
    return;
  }

  if (a)
  {
    switch (a->getType())
    {
      case armorType::HEAD:
        if (armor_head_.getRarity() >= 0)
          inventory_.addItem(armor_head_);  // And also here for Armor
        armor_head_ = *a;
        inventory_.removeItem(index);
        break;
      case armorType::CHEST:
        if (armor_chest_.getRarity() >= 0)
          inventory_.addItem(armor_chest_);
        armor_chest_ = *a;
        inventory_.removeItem(index);
        break;
      case armorType::ARMS:
        if (armor_arms_.getRarity() >= 0)
          inventory_.addItem(armor_arms_);
        armor_arms_ = *a;
        inventory_.removeItem(index);
        break;
      case armorType::LEGS:
        if (armor_legs_.getRarity() >= 0)
          inventory_.addItem(armor_legs_);
        armor_legs_ = *a;
        inventory_.removeItem(index);
        break;
      default:
        std::cout << "ERROR ARMOR TYPE INVALID!"
                  << "\n\n";
        return;
    }
    return;
  }
  std::cout << "ERROR EQUIP ITEM, ITEM IS NOT ARMOR OR WEAPON!";
  return;
}

void Character::removeItem(const int index)
{
  if (index < 0 || index >= inventory_.size())
    std::cout << "ERROR, NOT POSSIBLE TO REMOVE ITEM, removeItem Character"
              << "\n\n";
  else
  {
    inventory_.removeItem(index);
  }
}

const Item& Character::getItem(const int index)
{
  if (index < 0 || index >= inventory_.size())
  {
    std::cout << "ERROR, NOT POSSIBLE TO REMOVE ITEM, getItem Character"
              << "\n\n";
    throw("ERROR OUT OF BOUNDS, GETITEM CHARACTER");
  }

  return *(inventory_[index]);
}

void Character::takeDamage(const int damage)
{
  hp_ -= damage;

  if (hp_ <= 0)
  {
    hp_ = 0;
  }
}

void Character::resetHP()
{
  hp_ = hp_max_;
}

void Character::addItem(const Item& item)
{
  inventory_.addItem(item);
}

const int& Character::getDistTravel() const
{
  return distance_traveled_;
}
const std::string& Character::getName() const
{
  return name_;
}
const int& Character::getLevel() const
{
  return level_;
}
const int& Character::getExp() const
{
  return exp_;
}
const int& Character::getExpNext() const
{
  return expNext_;
}
const int& Character::getStatPoints() const
{
  return stat_points_;
}
const int& Character::getHP() const
{
  return hp_;
}
const int& Character::getHPMax() const
{
  return hp_max_;
}
const bool Character::isAlive()
{
  return hp_ > 0;
}
const int& Character::getStamina() const
{
  return stamina_;
}
const int& Character::getDamageMin() const
{
  return damage_min_;
}
const int& Character::getDamageMax() const
{
  return damage_max_;
}
const int Character::getDamage() const
{
  return rand() % (damage_max_ + weapon_.getDamageMax()) + (damage_min_ + weapon_.getDamageMin());
}
const int& Character::getDefense() const
{
  return defense_;
}
const int Character::getAddedDefense() const
{
  return armor_arms_.getDefense() + armor_chest_.getDefense() + armor_legs_.getDefense() + armor_head_.getDefense();
}
const int& Character::getAccuracy() const
{
  return accuracy_;
}
const int Character::getGold() const
{
  return gold_;
}
const int Character::getInventorySize() const
{
  return inventory_.size();
}

void Character::setDistTravelled(const int& distance)
{
  distance_traveled_ = distance;
}
void Character::travel()
{
  distance_traveled_++;
}
void Character::gainExp(const int exp)
{
  exp_ += exp;
}
void Character::gainGold(const int gold)
{
  gold_ += gold;
}
void Character::payGold(const int gold)
{
  gold_ -= gold;
}
void Character::setWeapon(Weapon weapon)
{
  weapon_ = weapon;
}
void Character::setArmorHead(Armor armor_head)
{
  armor_head_ = armor_head;
}
void Character::setArmorChest(Armor armor_chest)
{
  armor_chest_ = armor_chest;
}
void Character::setArmorArms(Armor armor_arms)
{
  armor_arms_ = armor_arms;
}
void Character::setArmorLegs(Armor armor_legs)
{
  armor_legs_ = armor_legs;
}
