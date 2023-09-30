#include "gtest/gtest.h"
#include "Inventory.h"

// TODO: Use Rarity enum type instead of int

TEST(InventoryTests, Initialization)
{
  Inventory inventory;
  ASSERT_EQ(inventory.size(), 0);
}

TEST(InventoryTests, AddMultipleItems)
{
  Inventory inventory;
  Weapon sword(0, 1, "Sword", 1, 10, 15, 0);
  Armor shield(0, 1, "Shield", 1, 10, 15, 0);

  inventory.addItem(sword);
  inventory.addItem(shield);

  ASSERT_EQ(inventory.size(), 2);

  auto clone_0 = inventory[0]->clone();
  auto clonedWeapon = dynamic_cast<Weapon*>(clone_0.get());
  ASSERT_TRUE(clonedWeapon != nullptr);
  EXPECT_EQ(clonedWeapon->getName(), sword.getName());
  // Add more checks for other attributes if needed

  auto clone_1 = inventory[1]->clone();
  auto clonedArmor = dynamic_cast<Armor*>(clone_1.get());
  ASSERT_TRUE(clonedArmor != nullptr);
  EXPECT_EQ(clonedArmor->getName(), shield.getName());
  // Add more checks for other attributes if needed
}

TEST(InventoryTests, RemoveFromEmptyInventory)
{
  Inventory inventory;
  ASSERT_THROW(inventory.removeItem(0), std::runtime_error);
}

TEST(InventoryTests, AccessOutOfBound)
{
  Inventory inventory;
  Weapon sword(0, 1, "Sword", 1, 10, 15, 0);

  inventory.addItem(sword);
  ASSERT_THROW(inventory[5], const char*);
}

TEST(InventoryTests, CopyConstructor)
{
  Inventory inventory1;
  Weapon sword(0, 1, "Sword", 1, 10, 15, 0);

  inventory1.addItem(sword);
  Inventory inventory2 = inventory1;

  inventory1.removeItem(0);
  ASSERT_EQ(inventory1.size(), 0);
  ASSERT_EQ(inventory2.size(), 1);
}

TEST(InventoryTests, MoveConstructor)
{
  Inventory inventory1;
  Weapon sword(0, 1, "Sword", 1, 10, 15, 0);

  inventory1.addItem(sword);
  Inventory inventory2 = std::move(inventory1);

  ASSERT_EQ(inventory1.size(), 0);
  ASSERT_EQ(inventory2.size(), 1);
}

TEST(InventoryTests, MoveAssignment)
{
  Inventory inventory1, inventory2;
  Weapon sword(0, 1, "Sword", 1, 10, 15, 0);

  inventory1.addItem(sword);
  inventory2 = std::move(inventory1);

  ASSERT_EQ(inventory1.size(), 0);
  ASSERT_EQ(inventory2.size(), 1);
}

TEST(InventoryTests, NonInitializedInventorySize)
{
  Inventory inventory;
  ASSERT_EQ(inventory.size(), 0);
}

// Make sure to include other necessary headers and main() for the test runner.
// Also ensure that the necessary dependencies are linked.
