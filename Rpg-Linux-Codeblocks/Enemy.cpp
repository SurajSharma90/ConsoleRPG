#include "Enemy.h"

Enemy::Enemy(int level)
{
	this->level = level;
	this->hpMax = rand()% (level * 10) + (level * 2);
	this->hp = this->hpMax;
	this->damageMin = this->level * 1;
	this->damageMax = this->level * 2;
	this->dropChance = rand() % 100 + 1;
	this->defence = rand() % level*5 + 1;
	this->accuracy = rand() % level*5 + 1;
}

Enemy::~Enemy()
{

}

std::string Enemy::getAsString()const
{
    std::stringstream ss;


    ss << "Level: " << this->level << "\n" <<
		"Hp: " << this->hp << " / " << this->hpMax << "\n" <<
		"Damage: " << this->damageMin << " - " << this->damageMax << "\n" <<
		"Defence: " << this->defence << "\n" <<
		"Accuracy: " << this->accuracy << "\n" <<
		"Drop chance: " << this->dropChance << "\n";

    return ss.str();
}

void Enemy::takeDamage(int damage)
{
	this->hp -= damage;

	if (this->hp <= 0)
	{
		this->hp = 0;
	}
}
