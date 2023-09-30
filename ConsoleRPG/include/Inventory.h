#pragma once

#include "STLINCLUDE.h"
#include "Weapon.h"
#include "Armor.h"
#include <functional>  // For std::bind in sort method
class Inventory
{
private:
  std::unique_ptr<std::vector<std::shared_ptr<Item>>> itemArr;
  bool compareItems(const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b);

public:
  Inventory();
  ~Inventory();
  Inventory(const Inventory& other);
  Inventory(Inventory&& other) noexcept;
  Inventory& operator=(Inventory&& other) noexcept;

  inline int size() const
  {
    return itemArr->size();
  };
  std::shared_ptr<Item>& operator[](const int index);
  void addItem(const Item& item);
  void removeItem(int index);
  inline void debugPrint() const
  {
    for (const auto& vec : (*itemArr))
    {
      std::cout << vec->debugPrint() << std::endl;
    }
  }
};
