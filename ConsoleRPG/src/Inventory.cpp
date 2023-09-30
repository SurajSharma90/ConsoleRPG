#include "Inventory.h"

Inventory::Inventory() : itemArr(nullptr)
{
}

Inventory::~Inventory()
{
}

Inventory::Inventory(const Inventory& other)
{
  if (other.itemArr)
  {
    // Deep copy the items in the vector
    this->itemArr = std::make_unique<std::vector<std::shared_ptr<Item>>>();
    for (const auto& item : *other.itemArr)
    {
      this->itemArr->push_back(item->clone());
    }
  }
  else
  {
    this->itemArr = nullptr;
  }
}

Inventory::Inventory(Inventory&& other) noexcept : itemArr(std::move(other.itemArr))
{
}

Inventory& Inventory::operator=(Inventory&& other) noexcept
{
  if (this != &other)
  {
    this->itemArr = std::move(other.itemArr);
  }
  return *this;
}

std::shared_ptr<Item>& Inventory::operator[](const int index)
{
  if (!itemArr)
  {
    throw std::runtime_error("Non Initialized Pointer");
  }
  if (index < 0 || index >= itemArr->size())
  {
    throw("BAD INDEX!");
  }

  return (*itemArr)[index];
}

void Inventory::addItem(const Item& item)
{
  if (!itemArr)
  {
    itemArr = std::make_unique<std::vector<std::shared_ptr<Item>>>();
  }
  itemArr->push_back(item.clone());
  // TODO: Every time something is bought, the whole inventory updates
  // TODO: Check where the removeItem and operator[] are being used, to avoid accessing the wrong memory
  //  std::sort(itemArr->begin(), itemArr->end(),
  //            std::bind(&Inventory::compareItems, this, std::placeholders::_1, std::placeholders::_2));
}

void Inventory::removeItem(int index)
{
  if (!itemArr)
  {
    throw std::runtime_error("Non Initialized Pointer");
  }
  if (index < 0 || index >= itemArr->size())
  {
    throw("BAD INDEX!");
  }
  itemArr->erase(itemArr->begin() + index);
}

bool Inventory::compareItems(const std::shared_ptr<Item>& a, const std::shared_ptr<Item>& b)
{
  if (a->getItemType() < b->getItemType())
    return true;
  else if (a->getItemType() == b->getItemType())
    return a->getRarity() > b->getRarity();  // Assuming higher rarity is better
  return false;
}

int Inventory::size() const
{
  if (!itemArr)
  {
    std::cout << "Inventory not initialized" << std::endl;
    return 0;
  }
  return itemArr->size();
}

void Inventory::debugPrint() const
{
  if (!itemArr)
  {
    std::cout << "Inventory not initialized" << std::endl;
    return;
  }

  for (const auto& vec : (*itemArr))
  {
    std::cout << vec->debugPrint() << std::endl;
  }
}