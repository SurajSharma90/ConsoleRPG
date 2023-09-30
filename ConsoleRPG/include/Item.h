#pragma once

#include "STLINCLUDE.h"

enum itemTypes
{
  WEAPON = 0,
  ARMOR
};

class Item
{
private:
  int itemType;
  std::string name;
  int level;
  int buyValue;
  int sellValue;
  int rarity;

public:
  Item();
  Item(int itemType, int level, int rarity);
  Item(int itemType, std::string name, int level, int buyValue, int sellValue, int rarity);
  virtual ~Item();

  std::string debugPrint() const;
  virtual std::shared_ptr<Item> clone() const = 0;
  virtual std::string toString() const = 0;
  virtual std::string toStringSave() const = 0;

  // Accessors
  const std::string& getName() const;
  const int& getLevel() const;
  const int& getBuyValue() const;
  const int& getSellValue() const;
  const int& getRarity() const;
  const int& getItemType() const;

  // Modifiers
  void setName(std::string name);
};

// TODO: Use this enum class
enum class Rarity
{
  COMMON = 0,
  UNCOMMON,
  RARE,
  LEGENDARY,
  MYTHIC
};
