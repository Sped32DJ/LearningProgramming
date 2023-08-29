
using namespace std;

#ifndef __WARRIOR_H__
#define __WARRIOR_H__

#include "Character.h"
#include <string>

class Warrior : public Character {
public:
  Warrior(const string &name, double health, double attackStrength,
          string allegiance);
  void attack(Character &target) override;
  string getAllegiance();
  /* ~Warrior();                              // Destructor declaration */
private:
  string allegiance;
};

#endif
