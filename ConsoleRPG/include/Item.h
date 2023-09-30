#pragma once

#include "STLINCLUDE.h"

enum ItemTypes
{
  WEAPON = 0,
  ARMOR
};

class Item
{
private:
  int item_type_;
  std::string name_;
  int level_;
  int buy_value_;
  int sell_value_;
  int rarity_;

public:
  Item(int item_type, int level, int rarity);
  Item(int item_type, std::string name, int level, int buy_value, int sell_value, int rarity);
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
