#include "gtest/gtest.h"
#include "Armor.h"

TEST(ArmorTest, InitNamesTest)
{
  Armor::initNames();
  EXPECT_EQ(Armor::names.size(), 6);
  EXPECT_EQ(Armor::names[0], "Bro-Saver");
  // ... continue for other names if needed
}

TEST(ArmorTest, ParameterizedConstructorTest)
{
  Armor armor(10, 4);
  EXPECT_GE(armor.getDefense(), 0);  // More specific tests based on your logic
  EXPECT_LE(armor.getType(), 3);
  EXPECT_GE(armor.getType(), 0);
  // ... You may want to add more checks based on rarity and level logic
}

TEST(ArmorTest, CloneTest)
{
  Armor armor(10, 4);
  std::shared_ptr<Item> cloned = armor.clone();
  Armor* clonedArmor = dynamic_cast<Armor*>(cloned.get());
  EXPECT_TRUE(clonedArmor != nullptr);
  EXPECT_EQ(clonedArmor->getDefense(), armor.getDefense());
  // ... Continue for other attributes
}

TEST(ArmorTest, ToStringTest)
{
  Armor armor(HEAD, 100, "TestArmor", 10, 500, 250, 3);
  std::string expected = "TestArmor | Type: Head | Lvl: 10 | Rarity: 3 | Def: 100";
  EXPECT_EQ(armor.toString(), expected);
}

TEST(ArmorTest, ToStringSaveTest)
{
  Armor armor(HEAD, 100, "TestArmor", 10, 500, 250, 3);
  std::string expected = "1 TestArmor 10 3 500 250 100 0 ";
  EXPECT_EQ(armor.toStringSave(), expected);
}

int main(int argc, char** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
