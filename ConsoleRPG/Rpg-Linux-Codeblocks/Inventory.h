#pragma once

#include"STLINCLUDE.h"
#include"Weapon.h"
#include"Armor.h"

class Inventory
{
private:
	int cap;
	int nrOfItems;
	Item **itemArr;
	void expand();
	void initialize(const int from = 0);

public:
	Inventory();
	~Inventory();
	Inventory(const Inventory &obj);
	inline int size()const { return this->nrOfItems; };
	Item& operator[](const int index);
	void operator=(const Inventory &obj);
	void addItem(const Item &item);
	void removeItem(int index);
	inline void debugPrint() const
	{
		for (size_t i = 0; i < this->nrOfItems; i++)
		{
			std::cout << this->itemArr[i]->debugPrint() << std::endl;
		}
	}
};

