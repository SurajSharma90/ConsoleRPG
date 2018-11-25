#include "Character.h"

Character::Character()
{
	this->distanceTravelled = 0;

	this->gold = 0;

	this->name = "";
	this->level = 0;
	this->exp = 0;
	this->expNext = 0;

	this->strength = 0;
	this->vitality = 0;
	this->dexterity = 0;
	this->intelligence = 0;

	this->hp = 0;
	this->hpMax = 0;
	this->stamina = 0;
	this->staminaMax = 0;
	this->damageMin = 0;
	this->damageMax = 0;
	this->defence = 0;
	this->accuracy = 0;
	this->luck = 0;

	this->statPoints = 0;
}

Character::Character(string name, int distanceTravelled,
	int gold, int level,
	int exp, int strength, int vitality,
	int dexterity, int intelligence,
	int hp, int stamina, int statPoints)
{
	this->distanceTravelled = distanceTravelled;

	this->gold = gold;

	this->name = name;
	this->level = level;
	this->exp = exp;
	this->expNext = 0;

	this->strength = strength;
	this->vitality = vitality;
	this->dexterity = dexterity;
	this->intelligence = intelligence;

	this->hp = hp;
	this->hpMax = 0;
	this->stamina = stamina;
	this->staminaMax = 0;
	this->damageMin = 0;
	this->damageMax = 0;
	this->defence = 0;
	this->accuracy = 0;
	this->luck = 0;

	this->statPoints = statPoints;

	this->updateStats();
}

Character::~Character()
{

}

//Functions
void Character::initialize(const string name)
{
	this->distanceTravelled = 0;

	this->gold = 100;

	this->name = name;
	this->level = 1;
	this->exp = 0;

	this->strength = 5;
	this->vitality = 5;
	this->dexterity = 5;
	this->intelligence = 5;

	this->statPoints = 0;

	this->updateStats();
}

void Character::printStats() const
{
	cout << "= Character Sheet =" << "\n";
	cout << "= Name: " << this->name << "\n";
	cout << "= Level: " << this->level << "\n";
	cout << "= Exp: " << this->exp << "\n";
	cout << "= Exp to next level: " << this->expNext << "\n";
	cout << "= Statpoints: " << this->statPoints << "\n";
	cout << "\n";
	cout << "= Strenght: " << this->strength << "\n";
	cout << "= Vitality: " << this->vitality << "\n";
	cout << "= Dexterity: " << this->dexterity << "\n";
	cout << "= Intelligence: " << this->intelligence << "\n";
	cout << "\n";
	cout << "= HP: " << this->hp << " / " << this->hpMax << "\n";
	cout << "= Stamina: " << this->stamina << " / " << this->staminaMax << "\n";
	cout << "= Damage: " << this->damageMin << "( +" << this->weapon.getDamageMin() << ")" << " - "<< this->damageMax << "( +" << this->weapon.getDamageMax() << ")" << "\n";
	cout << "= Defence: " << this->defence << "\n" << "( +" << this->getAddedDefence() << ")";
	cout << "= Accuracy: " << this->accuracy << "\n";
	cout << "= Luck: " << this->luck << "\n";
	cout << "\n";
	cout << "= Distance Travelled: " << this->distanceTravelled << "\n";
	cout << "= Gold: " << this->gold << "\n";
	cout << "\n";
	cout << "= Weapon: " << this->weapon.getName()
		<< " Lvl: " << this->weapon.getLevel()
		<< " Dam: " << this->weapon.getDamageMin() << " - " << this->weapon.getDamageMax() << "\n";
	cout << "= Armor Head: " << this->armor_head.getName()
		<< " Lvl: " << this->armor_head.getLevel()
		<< " Def: " << this->armor_head.getDefence() << "\n";
	cout << "= Armor Chest: " << this->armor_chest.getName()
		<< " Lvl: " << this->armor_chest.getLevel()
		<< " Def: " << this->armor_chest.getDefence() << "\n";
	cout << "= Armor Arms: " << this->armor_arms.getName()
		<< " Lvl: " << this->armor_arms.getLevel()
		<< " Def: " << this->armor_arms.getDefence() << "\n";
	cout << "= Armor Legs: " << this->armor_legs.getName()
		<< " Lvl: " << this->armor_legs.getLevel()
		<< " Def: " << this->armor_legs.getDefence() << "\n" << "\n";
}

string Character::getAsString() const
{
    std::stringstream ss;

	ss << " "
		<< distanceTravelled << " "
		<< gold << " "
		<< level << " "
		<< exp << " "
		<< strength << " "
		<< vitality << " "
		<< dexterity << " "
		<< intelligence << " "
		<< hp << " "
		<< stamina << " "
		<< statPoints << " "
		<< this->weapon.toStringSave()
		<< this->armor_head.toStringSave()
		<< this->armor_chest.toStringSave()
		<< this->armor_arms.toStringSave()
		<< this->armor_legs.toStringSave();

    return ss.str();
}

string Character::getInvAsString(bool shop)
{
	std::stringstream ss;

	for (size_t i = 0; i < this->inventory.size(); i++)
	{
		if (shop)
		{
			ss << i << ": " << this->inventory[i].toString() << "\n" << " - Sell value: "
				<< this->inventory[i].getSellValue() << "\n";
		}
		else
		{
			ss << i << ": " << this->inventory[i].toString() << "\n";
		}
	}

	return ss.str();
}

string Character::getInvAsStringSave()
{
	string inv;

	for (size_t i = 0; i < this->inventory.size(); i++)
	{
		if(this->inventory[i].getItemType() == WEAPON)
			inv += this->inventory[i].toStringSave();
	}

	inv += "\n";

	for (size_t i = 0; i < this->inventory.size(); i++)
	{
		if (this->inventory[i].getItemType() == ARMOR)
			inv += this->inventory[i].toStringSave();
	}

	return inv;
}

void Character::levelUp()
{
	if (this->exp >= this->expNext)
	{
		this->exp -= this->expNext;
		this->level++;
		this->expNext = static_cast<int>((50 / 3)*((pow(level, 3)
			- 6 * pow(level, 2))
			+ 17 * level - 12)) + 100;

		this->statPoints++;

		this->updateStats();

		cout << "YOU ARE NOW LEVEL " << this->level << "!" << "\n\n";
	}
	else
	{
		cout << "NOT ENOUGH EXP!" << "\n\n";
	}
}

void Character::updateStats()
{
	this->expNext = static_cast<int>(
		(50 / 3)*((pow(level, 3)
			- 6 * pow(level, 2))
			+ 17 * level - 12)) + 100;

	this->hpMax = (this->vitality * 5) + (this->strength) + this->level*5;
	this->staminaMax = this->vitality + (this->strength / 2) + (this->dexterity / 3);
	this->stamina = this->staminaMax;
	this->damageMin = this->strength;
	this->damageMax = this->strength + 2;
	this->defence = this->dexterity + (this->intelligence / 2);
	this->accuracy = (this->dexterity / 2) + intelligence;
	this->luck = this->intelligence;

	this->hp = this->hpMax;
}

void Character::addToStat(int stat, int value)
{
	if (this->statPoints < value)
		cout << "ERROR! NOT ENOUGH STATPOINTS!" << "\n";
	else
	{
		switch (stat)
		{
		case 0:
			this->strength += value;
			cout << "STRENGTH INCREASED!" << "\n";

			break;

		case 1:
			this->vitality += value;
			cout << "VITALITY INCREASED!" << "\n";
			break;

		case 2:
			this->dexterity += value;
			cout << "DEXTERITY INCREASED!" << "\n";
			break;

		case 3:
			this->intelligence += value;
			cout << "INTELLIGENCE INCREASED!" << "\n";
			break;

		default:
			cout << "NO SUCH STAT!" << "\n";
			break;
		}

		this->statPoints -= value;

		this->updateStats();
	}
}

void Character::equipItem(unsigned index)
{
	if (index < 0 || index >= this->inventory.size())
	{
		cout << "No valid item selected!" << "\n\n";
	}
	else
	{
		Weapon *w = NULL;
		w = dynamic_cast<Weapon*>(&this->inventory[index]);

		Armor *a = NULL;
		a = dynamic_cast<Armor*>(&this->inventory[index]);

		//Is weapon
		if (w != NULL)
		{
			if (this->weapon.getRarity() >= 0)
				this->inventory.addItem(this->weapon);
			this->weapon = *w;
			this->inventory.removeItem(index);
		}
		else if (a != NULL)
		{
			switch (a->getType())
			{
			case HEAD:
				if (this->armor_head.getRarity() >= 0)
					this->inventory.addItem(this->armor_head);
				this->armor_head = *a;
				this->inventory.removeItem(index);
				break;
			case CHEST:
				if (this->armor_chest.getRarity() >= 0)
					this->inventory.addItem(this->armor_chest);
				this->armor_chest = *a;
				this->inventory.removeItem(index);
				break;
			case ARMS:
				if (this->armor_arms.getRarity() >= 0)
					this->inventory.addItem(this->armor_arms);
				this->armor_arms = *a;
				this->inventory.removeItem(index);
				break;
			case LEGS:
				if(this->armor_legs.getRarity() >= 0)
					this->inventory.addItem(this->armor_legs);
				this->armor_legs = *a;
				this->inventory.removeItem(index);
				break;
			default:
				cout << "ERROR ARMOR TYPE INVALID!" << "\n\n";
				break;
			}
		}
		else
		{
			cout << "ERROR EQUIP ITEM, ITEM IS NOT ARMOR OR WEAPON!";
		}
	}
}

void Character::removeItem(const int index)
{
	if (index < 0 || index >= this->inventory.size())
		cout << "ERROR, NOT POSSIBLE TO REMOVE ITEM, removeItem Character" << "\n\n";
	else
	{
		this->inventory.removeItem(index);
	}
}

const Item& Character::getItem(const int index)
{
	if (index < 0 || index >= this->inventory.size())
	{
		cout << "ERROR, NOT POSSIBLE TO REMOVE ITEM, getItem Character" << "\n\n";
		throw("ERROR OUT OF BOUNDS, GETITEM CHARACTER");
	}

	return this->inventory[index];
}

void Character::takeDamage(const int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}
