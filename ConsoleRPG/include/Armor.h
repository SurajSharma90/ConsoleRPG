#pragma once

#include "STLINCLUDE.h"
#include "Item.h"

enum armorType
{
  HEAD = 0,
  CHEST,
  ARMS,
  LEGS
};

class Armor : public Item
{
private:
  int type;
  std::string typeStr;
  int defense;

public:
  // TODO: Delete defaut constructor as it is not used
  Armor();
  Armor(int level, int rarity);
  Armor(int type, int defense, std::string name, int level, int buyValue, int sellValue, int rarity);
  ~Armor();

  // Pure virtual
  virtual std::shared_ptr<Item> clone() const override;

  // Functions
  std::string toString() const;
  std::string toStringSave() const;

  // Accessors
  inline int getDefense() const
  {
    return this->defense;
  }
  inline int getType() const
  {
    return this->type;
  }

  // Static
  static std::vector<std::string> names;
  static void initNames();
};