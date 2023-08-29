#include "Character.h"
#include <string>

using namespace std;

#ifndef __WIZARD_H__
#define __WIZARD_H__

class Wizard : public Character {
public:
  Wizard(const string &name, double health, double attackStrength, int rank);
  void attack(Character &target) override;
  int getRank() const;

private:
  int rank;
};

#endif
