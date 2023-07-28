#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

class Car {
public:
  void SetModelYear(int year);
  int GetModelYear() const;

  // TODO: Declare Setint() function
  void SetPurchasePrice(int price);

  // TODO: Declare GetPurchasePrice() function
  int GetPurchasePrice() const;

  void CalcCurrentValue(int currentYear);

  // TODO: Declare PrintInfo() method to output modelYear, purchasePrice, and
  // currentValue
  void PrintInfo() const;

private:
  int modelYear;
  // TODO: Declare purchasePrice member (int)
  int purchasePrice;
  int currentValue;
};

void Car::SetModelYear(int year) { modelYear = year; }

int Car::GetModelYear() const { return modelYear; }

// TODO: Implement SetPurchasePrice() function
void Car::SetPurchasePrice(int price) { purchasePrice = price; }

// TODO: Implement GetPurchasePrice() function
int Car::GetPurchasePrice() const { return purchasePrice; }

void Car::CalcCurrentValue(int currentYear) {
  double depreciationRate = 0.15;
  int carAge = currentYear - modelYear;

  // Car depreciation formula
  currentValue = purchasePrice * pow((1 - depreciationRate), carAge);
}

// TODO: Implement PrintInfo() function to output modelYear, purchasePrice, and
// currentValue
void Car::PrintInfo() const {
  cout << fixed << setprecision(0);
  cout << "Car's information:" << endl
       << " Model year: " << modelYear << endl
       << " Purchase price: " << purchasePrice << endl
       << " Current value: " << currentValue << endl;
}

int main() {
  int userYear;
  int userPrice;
  int userCurrentYear;
  Car myCar;

  cin >> userYear;
  cin >> userPrice;
  cin >> userCurrentYear;

  myCar.SetModelYear(userYear);
  myCar.SetPurchasePrice(userPrice);
  myCar.CalcCurrentValue(userCurrentYear);

  myCar.PrintInfo();

  return 0;
}
