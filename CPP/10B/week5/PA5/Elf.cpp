#include "Elf.h"
#include <iomanip>
#include <iostream>
#include <string>

Elf::Elf(const string &name, double health, double attackStrength,
         string familyName)
    : Character::Character(ELF, name, health, attackStrength),
      familyName(familyName) {}

void Elf::attack(Character &target) {
  // refuse to attack other elfs
  if (target.getType() == ELF) {
    Elf &elfTarget = dynamic_cast<Elf &>(target);

    if (elfTarget.getFamilyName() == this->getFamilyName()) {

      cout << "Elf " << getName() << " does not attack Elf "
           << elfTarget.getName() << '.' << endl;
      cout << "They are both members of the " << getFamilyName() << " family."
           << endl;
      return;
    }
  }
  double damage =
      (health / MAX_HEALTH) * attackStrength;
  target.damage(damage);
  cout << "Elf " << getName() << " shoots an arrow at " << target.getName()
       << " --- TWANG!!" << endl;
  cout << target.getName() << " takes " << setprecision(6) << damage
       << " damage." << endl;
}

string Elf::getFamilyName() { return familyName; }
