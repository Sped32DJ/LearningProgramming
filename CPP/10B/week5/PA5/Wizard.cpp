#include "Wizard.h"
#include <iomanip>
#include <iostream>
#include <string>

Wizard::Wizard(const string &name, double health, double attackStrength,
               int rank)
    : Character::Character(WIZARD, name, health, attackStrength), rank(rank) {}

void Wizard::attack(Character &target) {
  // If both wizards, dps differently
  if (target.getType() == WIZARD) {
    Wizard &WizTarget = dynamic_cast<Wizard &>(target);

    double damage = attackStrength * (static_cast<double>(this->getRank()) /
                                      static_cast<double>(WizTarget.getRank()));
    target.damage(damage);

    cout << "Wizard " << getName() << " attacks " << WizTarget.getName()
         << " --- POOF!!" << endl;
    cout << WizTarget.getName() << " takes " << setprecision(6) << damage
         << " damage." << endl;
    // double damage = attackStrength * (this->getRank() /
    // WizTarget.getRank())
    return;
  }

  double damage = attackStrength;
  target.damage(damage);
  cout << "Wizard " << getName() << " attacks " << target.getName()
       << " --- POOF!!" << endl;
  cout << target.getName() << " takes " << setprecision(6) << damage
       << " damage." << endl;
}

int Wizard::getRank() const { return rank; }
