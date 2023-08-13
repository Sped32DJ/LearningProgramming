#include <iostream>
#include <vector>
using namespace std;

class Purchase {
   public:
      bool ReadDetails();
      void Print() const;
   private:
      string food;
      char option;
};

bool Purchase::ReadDetails() {
	string newFood;

	cin >> newFood;
	if (newFood == "done") {
		return false;
	}
	else {
		food = newFood;
		cin >> option;
		return true;
	}
}

void Purchase::Print() const {
   cout << "Purchase: " << food << ", Option: " << option << endl;
}

class Deliveries {
   public:
      void InputPurchases();
      void PrintPurchases();
   private:
      vector<Purchase> purchaseList;
};

/* Your code goes here */
// =============
void Deliveries::InputPurchases(){
   Purchase result;
   while(result.ReadDetails()){
      purchaseList.push_back(result);
   }

}
// =============

void Deliveries::PrintPurchases() {
   Purchase currPurchase;
   unsigned int i;

   for (i = 0; i < purchaseList.size(); ++i) {
      currPurchase = purchaseList.at(i);
      currPurchase.Print();
   }
}

int main() {
   Deliveries deliveries;

   deliveries.InputPurchases();
   deliveries.PrintPurchases();

   return 0;
}
