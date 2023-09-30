#pragma once

#include "STLINCLUDE.h"
#include "Item.h"

class Weapon : public Item
{
private:
  int damageMin;
  int damageMax;

public:
  Weapon();
  Weapon(int level, int rarity);
  Weapon(int damageMin, int damageMax, std::string name, int level, int buyValue, int sellValue, int rarity);
  ~Weapon();

  // Pure virtual
  virtual std::shared_ptr<Item> clone() const override;

  // Functions
  std::string toString() const;
  std::string toStringSave() const;

  // Accessors
  inline int getDamageMin() const
  {
    return this->damageMin;
  }
  inline int getDamageMax() const
  {
    return this->damageMax;
  }

  // Modifiers

  // Static
  static std::vector<std::string> names;
  static void initNames();
};