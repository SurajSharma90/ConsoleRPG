#include "Enemy.h"

Enemy::Enemy(int level)
{
  level_ = level;
  hp_max_ = rand() % (level * 10) + (level * 2);
  hp_ = hp_max_;
  damage_min_ = level_ * 1;
  damage_max_ = level_ * 2;
  drop_change_ = rand() % 100 + 1;
  defense_ = rand() % level * 5 + 1;
  accuracy_ = rand() % level * 5 + 1;
}

Enemy::~Enemy()
{
}

std::string Enemy::getAsString() const
{
  return "Level: " + std::to_string(level_) + "\n" + "Hp: " + std::to_string(hp_) + " / " + std::to_string(hp_max_) +
         "\n" + "Damage: " + std::to_string(damage_min_) + " - " + std::to_string(damage_max_) + "\n" +
         "Defense: " + std::to_string(defense_) + "\n" + "Accuracy: " + std::to_string(accuracy_) + "\n" +
         "Drop chance: " + std::to_string(drop_change_) + "\n";
}

void Enemy::takeDamage(int damage)
{
  hp_ -= damage;

  if (hp_ <= 0)
  {
    hp_ = 0;
  }
}