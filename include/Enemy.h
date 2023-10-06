#pragma once

#include "STLINCLUDE.h"

class Enemy
{
private:
  int level_;
  int hp_;
  int hp_max_;
  int damage_min_;
  int damage_max_;
  float drop_change_;
  int defense_;
  int accuracy_;

public:
  Enemy(int level = 0);
  virtual ~Enemy();

  inline bool isAlive()
  {
    return hp_ > 0;
  }
  std::string getAsString() const;
  void takeDamage(int damage);

  inline int getLevel() const
  {
    return level_;
  }
  inline int getDamageMin() const
  {
    return damage_min_;
  }
  inline int getDamageMax() const
  {
    return damage_max_;
  }
  inline int getDamage() const
  {
    return rand() % damage_max_ + damage_min_;
  }
  inline int getExp() const
  {
    return level_ * 100;
  }
  inline int getHp() const
  {
    return hp_;
  }
  inline int getHpMax() const
  {
    return hp_max_;
  }
  inline int getDefense() const
  {
    return defense_;
  }
  inline int getAccuracy() const
  {
    return accuracy_;
  }
};
