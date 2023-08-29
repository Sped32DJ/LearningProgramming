#include "Character.h"
#include <iostream>
#include <string>

using namespace std;

Character::Character(HeroType type, const string &name, double health,
                     double attackStrength)
    : type(type), name(name), health(health), attackStrength(attackStrength) {

  // TODO  When is MAX_HEALTH used?
  if (health > MAX_HEALTH) {
    this->health = MAX_HEALTH;
  }
}

HeroType Character::getType() const { return type; }

const string &Character::getName() const { return name; }

int Character::getHealth() const { return static_cast<int>(health); }

void Character::damage(double d) { this->health -= d; }

bool Character::isAlive() const { return (getHealth() > 0); }

/* virtual void Character::attack(Character &) = 0; */
