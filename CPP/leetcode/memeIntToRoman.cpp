#include <iostream>
#include <string>
// Solution to intToRoman and romanToInt

class Solution {
public:
  string intToRoman(int num) {
    size_t amount = 0; // will be used for push_back loops
    string roman;

    // M (1000)
    // CM (900)
    if (num / 900 > 0) {
      /* if (num % 900 == 0) { // Modulo should honestly be different */
      if (num % 1000 > 0) {
        amount = num / 1000;
        for (size_t i = 0; i < amount; ++i) {
          roman.push_back('M');
        }
      }
      if (num % 900 > 100) {
        roman.pop_back();
        roman.push_back('I');
        roman.push_back('M');
      } // If something about 999 = IM

      num %= 1000; // takes away what was just push_back
    }

    // D (500)
    // CD (400)
    if (num / 400 > 0) {
      if (num / 500 > 0) {
        amount = num / 500;
        for (size_t i = 0; i < amount; ++i) {
          roman.push_back('D');
        }
        num %= 400;
      }
      if (num % 500 = 400) {
        roman.push_back('I');
        roman.push_back('D');
        num %= 500;
      }
    }

    // C (100)
    // XC (90) NOTE  or is it 99?
    if (num / 90 > 0) {
      if (num / 90 == 1) {
        roman.push_back('X');
        roman.push_back('C');
        num %= 90;
      }
      if (num / 100 == 1) {
        roman.push_back('C');
        num %= 100;
      }
      amount = num / 100;
    }

    // L (50)
    // XL(40)
    if (num / 40 > 0) {
      if (num / 40 == 1) {
        roman.push_back('X');
        roman.push_back('L');
        num %= 40;
      }
      if (num / 50 == 1) {
        roman.push_back('L');
        num %= 50;
      }
    }

    // X (10)
    // IX (9)
    if (num / 9 > 0) {
      // TODO  There is probably a shorter way to write this
      if (num / 10 > 1) {
        amount = num / 10;
        for (size_t i = 0; i < amount; ++i) {
          roman.push_back('X');
        }
        num %= 10;
      }
      if (num / 9 == 1) {
        roman.push_back('I');
        roman.push_back('X');
        num %= 9;
      }
    }

    // V (5)
    // IV (4)
    // NOTE  Looks bulletproof to me
    if (num / 4 > 0) {
      if (num / 5 == 1) { // No need for for loops
        roman.push_back('V');
        num %= 5;
      }
      if (num / 4 == 1) {
        roman.push_back('I');
        roman.push_back('V');
        num %= 4;
      }
    }

    // If everything is to plan, this should work
    for (size_t i = 0; i < num; ++i) {
      roman.push_back('I');
    }

    return roman;
  }

  int romanToInt(string roman) {
    size_t num = 0;
    return num;
  }
};

int main() {
  Solution d;
  size_t number = 9999;
  cout << d.intToRoman(number) << endl;
  return 0;
}
