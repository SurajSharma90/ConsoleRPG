#pragma once

#include "STLINCLUDE.h"
#include "Item.h"

class Weapon : public Item
{
private:
  int damage_min_;
  int damage_max_;

public:
  Weapon(int level, int rarity);
  Weapon(int damage_min, int damage_max, std::string name, int level, int buy_value, int sell_value, int rarity);
  ~Weapon();

  // Pure virtual
  virtual std::shared_ptr<Item> clone() const override;

  // Functions
  std::string toString() const;
  std::string toStringSave() const;

  // Accessors
  inline int getDamageMin() const
  {
    return damage_min_;
  }
  inline int getDamageMax() const
  {
    return damage_max_;
  }

  // Modifiers

  // Static
  static std::vector<std::string> names;
  static void initNames();
};