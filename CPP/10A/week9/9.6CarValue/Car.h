#ifndef CARH
#define CARH

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

#endif

