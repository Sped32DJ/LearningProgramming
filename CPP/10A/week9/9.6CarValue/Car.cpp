#include "Car.h"
#include <cmath>
#include <iomanip>
#include <iostream>
using namespace std;

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
       << "  Model year: " << modelYear << endl
       << "  Purchase price: $" << purchasePrice << endl
       << "  Current value: $" << currentValue << endl;
}

