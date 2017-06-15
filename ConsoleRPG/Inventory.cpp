#include "Inventory.h"

Inventory::Inventory()
{
	this->cap = 5;
	this->nrOfItems = 0;
	this->itemArr = new Item*[cap];
	this->initialize();
}

Inventory::~Inventory()
{
	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		delete this->itemArr[i];
	}
	delete[] this->itemArr;
}

Inventory::Inventory(const Inventory &obj)
{
	this->cap = obj.cap;
	this->nrOfItems = obj.nrOfItems;
	this->itemArr = new Item*[this->cap];

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		this->itemArr[i] = obj.itemArr[i]->clone();
	}

	initialize(this->nrOfItems);
}

Item& Inventory::operator[](const int index)
{
	if (index < 0 || index >= this->nrOfItems)
		throw("BAD INDEX!");

	return *this->itemArr[index];
}

void Inventory::expand()
{
	this->cap *= 2;

	Item **tempArr = new Item*[this->cap];

	for (size_t i = 0; i < this->nrOfItems; i++)
	{
		tempArr[i] = this->itemArr[i];
	}

	delete[] this->itemArr;

	this->itemArr = tempArr;

	this->initialize(this->nrOfItems);
}

void Inventory::initialize(const int from)
{
	for (size_t i = from; i < cap; i++)
	{
		this->itemArr[i] = nullptr;
	}
}

void Inventory::addItem(const Item &item)
{
	if (this->nrOfItems >= this->cap)
	{
		expand();
	}

	this->itemArr[this->nrOfItems++] = item.clone();
}

void Inventory::removeItem(int index)
{

}