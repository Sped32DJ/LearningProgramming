#include "Character.h"
#include <string>

using namespace std;

#ifndef __ELF_H__
#define __ELF_H__

class Elf : public Character {
public:
  Elf(const string &name, double health, double attackStrength,
      string familyName);
  void attack(Character &target) override;
  string getFamilyName();

private:
  string familyName;
};

#endif
