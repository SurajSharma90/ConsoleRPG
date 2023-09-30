#include "Inventory.h"

Inventory::Inventory() : item_vec_ptr_(nullptr)
{
}

Inventory::~Inventory()
{
}

Inventory::Inventory(const Inventory& other)
{
  if (other.item_vec_ptr_)
  {
    // Deep copy the items in the vector
    item_vec_ptr_ = std::make_unique<std::vector<std::shared_ptr<Item>>>();
    for (const auto& item : *other.item_vec_ptr_)
    {
      item_vec_ptr_->push_back(item->clone());
    }
  }
  else
  {
    item_vec_ptr_ = nullptr;
  }
}

Inventory::Inventory(Inventory&& other) noexcept : item_vec_ptr_(std::move(other.item_vec_ptr_))
{
}

Inventory& Inventory::operator=(Inventory&& other) noexcept
{
  if (this != &other)
  {
    item_vec_ptr_ = std::move(other.item_vec_ptr_);
  }
  return *this;
}

std::shared_ptr<Item>& Inventory::operator[](const int index)
{
  if (!item_vec_ptr_)
  {
    throw std::runtime_error("Non Initialized Pointer");
  }
  if (index < 0 || index >= item_vec_ptr_->size())
  {
    throw("BAD INDEX!");
  }

  return (*item_vec_ptr_)[index];
}

void Inventory::addItem(const Item& item)
{
  if (!item_vec_ptr_)
  {
    item_vec_ptr_ = std::make_unique<std::vector<std::shared_ptr<Item>>>();
  }
  item_vec_ptr_->push_back(item.clone());
  // TODO: Every time something is bought, the whole inventory updates
  // TODO: Check where the removeItem and operator[] are being used, to avoid accessing the wrong memory
  //  std::sort(item_vec_ptr_->begin(), item_vec_ptr_->end(),
  //            std::bind(&Inventory::compareItems, this, std::placeholders::_1, std::placeholders::_2));
}

void Inventory::removeItem(int index)
{
  if (!item_vec_ptr_)
  {
    throw std::runtime_error("Non Initialized Pointer");
  }
  if (index < 0 || index >= item_vec_ptr_->size())
  {
    throw("BAD INDEX!");
  }
  item_vec_ptr_->erase(item_vec_ptr_->begin() + index);
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
  if (!item_vec_ptr_)
  {
    std::cout << "Inventory not initialized" << std::endl;
    return 0;
  }
  return item_vec_ptr_->size();
}

void Inventory::debugPrint() const
{
  if (!item_vec_ptr_)
  {
    std::cout << "Inventory not initialized" << std::endl;
    return;
  }

  for (const auto& vec : (*item_vec_ptr_))
  {
    std::cout << vec->debugPrint() << std::endl;
  }
}