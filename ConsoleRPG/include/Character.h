#pragma once

#include <math.h>

#include "Inventory.h"
#include "STLINCLUDE.h"

class Character
{
private:
  int distance_traveled_;

  Inventory inventory_;
  Weapon weapon_;
  Armor armor_head_;
  Armor armor_chest_;
  Armor armor_arms_;
  Armor armor_legs_;
  int gold_;

  std::string name_;
  int level_;
  int exp_;
  int expNext_;

  int strength_;
  int vitality_;
  int dexterity_;
  int intelligence_;

  int hp_;
  int hp_max_;
  int stamina_;
  int staminaMax_;
  int damage_min_;
  int damage_max_;
  int defense_;
  int accuracy_;
  // TODO: Add luck to the system
  int luck_;

  int stat_points_;

public:
  Character();
  Character(std::string name, int distance_traveled, int gold, int level, int exp, int strength, int vitality,
            int dexterity, int intelligence, int hp, int stamina, int stat_points);
  ~Character();

  // Functions
  void initialize(const std::string name);
  void printStats() const;
  std::string getAsString() const;
  std::string getInvAsString(bool shop = false);
  std::string getInvAsStringSave();
  void levelUp();
  void updateStats();
  void addToStat(int stat, int value);
  void equipItem(unsigned index);
  void resetHP();
  void addItem(const Item& item);
  void removeItem(const int index);
  const Item& getItem(const int index);

  // Accessors
  const int& getDistTravel() const;
  const std::string& getName() const;
  const int& getLevel() const;
  const int& getExp() const;
  const int& getExpNext() const;
  const int& getStatPoints() const;
  const int& getHP() const;
  const int& getHPMax() const;
  const bool isAlive();
  const int& getStamina() const;
  const int& getDamageMin() const;
  const int& getDamageMax() const;
  const int getDamage() const;
  const int& getDefense() const;
  const int getAddedDefense() const;
  const int& getAccuracy() const;
  const int getGold() const;
  const int getInventorySize() const;

  // Modifier
  void setDistTravelled(const int& distance);
  void travel();
  void gainExp(const int exp);
  void gainGold(const int gold);
  void payGold(const int gold);
  void takeDamage(const int damage);
  void setWeapon(Weapon weapon);
  void setArmorHead(Armor armor_head);
  void setArmorChest(Armor armor_chest);
  void setArmorArms(Armor armor_arms);
  void setArmorLegs(Armor armor_legs);
};
