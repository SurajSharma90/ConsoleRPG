#pragma once

#include"STLINCLUDE.h"
#include"Inventory.h"

using namespace std;

class Character
{
private:

	int distanceTravelled;

	Inventory inventory;
	Weapon weapon;
	Armor armor_head;
	Armor armor_chest;
	Armor armor_arms;
	Armor armor_legs;
	int gold;

	std::string name;
	int level;
	int exp;
	int expNext;

	int strength;
	int vitality;
	int dexterity;
	int intelligence;

	int hp;
	int hpMax;
	int stamina;
	int staminaMax;
	int damageMin;
	int damageMax;
	int defence;
	int accuracy;
	int luck;

	int statPoints;

public:
	Character();
	Character(string name, int distanceTravelled,
		int gold, int level,
		int exp, int strength, int vitality,
		int dexterity, int intelligence,
		int hp, int stamina, int statPoints);
	virtual ~Character();

	//Functions
	void initialize(const std::string name);
	void printStats() const;
	string getAsString()const;
	string getInvAsString(bool shop = false);
	string getInvAsStringSave();
	void levelUp();
	void updateStats();
	void addToStat(int stat, int value);
	void equipItem(unsigned index);
	inline void resetHP() { this->hp = this->hpMax; }
	void addItem(const Item &item) { this->inventory.addItem(item); }
	void removeItem(const int index);
	const Item& getItem(const int index);

	//Accessors
	inline const int& getDistTravel() const { return this->distanceTravelled; }
	inline const std::string& getName() const { return this->name; }
	inline const int& getLevel() const { return this->level; }
	inline const int& getExp() const { return this->exp; }
	inline const int& getExpNext() const { return this->expNext; }
	inline const int& getStatPoints() const { return this->statPoints; }
	inline const int& getHP() const { return this->hp; }
	inline const int& getHPMax() const { return this->hpMax; }
	inline const bool isAlive() { return this->hp > 0; }
	inline const int& getStamina() const { return this->stamina; }
	inline const int& getDamageMin() const { return this->damageMin; }
	inline const int& getDamageMax() const { return this->damageMax; }
	inline const int getDamage()const { return rand() % (this->damageMax + this->weapon.getDamageMax()) + (this->damageMin + this->weapon.getDamageMin()); }
	inline const int& getDefence() const { return this->defence; }
	inline const int getAddedDefence()const { return this->armor_arms.getDefence() + this->armor_chest.getDefence() + this->armor_legs.getDefence() + this->armor_head.getDefence(); }
	inline const int& getAccuracy() const { return this->accuracy; }
	inline const int getGold() const { return this->gold; }
	inline const int getInventorySize()const { return this->inventory.size(); }

	//Modifier
	inline void setDistTravelled(const int& distance) { this->distanceTravelled = distance; }
	inline void travel() { this->distanceTravelled++; }
	inline void gainExp(const int exp) { this->exp += exp; }
	inline void gainGold(const int gold) { this->gold += gold; }
	inline void payGold(const int gold) { this->gold -= gold; }
	void takeDamage(const int damage);
	inline void setWeapon(Weapon weapon) { this->weapon = weapon; }
	inline void setArmorHead(Armor armor_head) { this->armor_head = armor_head; }
	inline void setArmorChest(Armor armor_chest) { this->armor_chest = armor_chest; }
	inline void setArmorArms(Armor armor_arms) { this->armor_arms = armor_arms; }
	inline void setArmorLegs(Armor armor_legs) { this->armor_legs = armor_legs; }
};

