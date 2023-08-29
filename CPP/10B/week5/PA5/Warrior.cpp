#include "Warrior.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

Warrior::Warrior(const string &name, double health, double attackStrength,
                 string allegiance)
    : Character::Character(WARRIOR, name, health, attackStrength),
      allegiance(allegiance) {}

void Warrior::attack(Character &target) {
  // If same allegiance, no attack
  if (target.getType() == WARRIOR) {
    Warrior &WarriorTarget = dynamic_cast<Warrior &>(target);
    if (WarriorTarget.getAllegiance() == getAllegiance()) {
      cout << "Warrior " << getName() << " does not attack Warrior "
           << WarriorTarget.getName() << '.' << endl;
      cout << "They share an allegiance with " << getAllegiance() << '.'
           << endl;
      return;
    }
  }
  double damage = (this->health / MAX_HEALTH) * attackStrength;
  target.damage(damage);
  cout << "Warrior " << getName() << " attacks " << target.getName()
       << " --- SLASH!!" << endl;
  cout << target.getName() << " takes " << setprecision(6) << damage
       << " damage." << endl;
}
string Warrior::getAllegiance() { return allegiance; }
