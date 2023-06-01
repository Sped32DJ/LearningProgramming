#include <iostream>
using namespace std;

class Quail {
public:
  string GetName() const;
  int GetAge() const;
  string GetColor() const;
  /* Member function declarations go here */
  string SetName() const;
  int SetAge() const;
  string SetColor() const;

private:
  string name;
  int age;
  string color;
  /* Data members go here */
};

void Quail::SetName(string customName) { name = customName; }

void Quail::SetAge(int customAge) { age = customAge; }

void Quail::SetColor(string customColor) { color = customColor; }

string Quail::GetName() const { return name; }

int Quail::GetAge() const { return age; }

string Quail::GetColor() const { return color; }

int main() {
  Quail quail1;
  string userName;
  int userAge;
  string userColor;

  cin >> userName;
  cin >> userAge;
  cin >> userColor;

  quail1.SetName(userName);
  quail1.SetAge(userAge);
  quail1.SetColor(userColor);
  cout << "Name: " << quail1.GetName() << endl;
  cout << "Age: " << quail1.GetAge() << endl;
  cout << "Color: " << quail1.GetColor() << endl;

  return 0;
}
