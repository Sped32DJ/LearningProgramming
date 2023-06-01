#ifndef CARH
#define CARH

class Car {
private:
  int modelYear;
  // TODO: Declare purchasePrice member (int)
  double purchasePrice;
  double currentValue;

public:
  void SetModelYear(int userYear);

  int GetModelYear() const;

  // TODO: Declare SetPurchasePrice() function
  void SetPurchasePrice(int purchasePrice) const;

  // TODO: Declare GetPurchasePrice() function
  double GetPurchasePrice() const;

  void CalcCurrentValue(int currentYear) const;

  // TODO: Declare PrintInfo() method to output modelYear, purchasePrice, and
  // currentValue
  void PrintInfo() const;
};

#endif
