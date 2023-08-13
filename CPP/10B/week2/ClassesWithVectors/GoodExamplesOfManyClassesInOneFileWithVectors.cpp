// "New" means new compared to previous level
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Product {
   public:
      void SetPriceAndName(int productPrice, string productName) {
         price = productPrice;
         name = productName;
      };
      int GetPrice() const { return price; };
      string GetName() const { return name; };
   private:
      int price; // in dollars
      string name;
};
// END Product class

class Products {
   public:
      void InputProducts();
      void PrintAfterDiscount(int discountPrice);
   private:
      vector<Product> productList;
};

void Products::InputProducts() {
   Product currProduct;
   int currPrice;
   string currName;

   cin >> currPrice;
   while (currPrice > 0) {
      cin >> currName;
      currProduct.SetPriceAndName(currPrice, currName);
      productList.push_back(currProduct);
      cin >> currPrice;
   }
}

void Products::PrintAfterDiscount(int discountPrice) {
   unsigned int i;
   int currDiscountPrice;

   for (i = 0; i < productList.size(); ++i) {
      currDiscountPrice = productList.at(i).GetPrice() - discountPrice;
      cout << productList.at(i).GetName() << ": " << currDiscountPrice << endl;
   }
}
// END Products class

// New: Store class has been added
class Store {
   public:
      void SetName(string storeName) {
         name = storeName;
      }
      void ReadAllProducts();
      void PrintSale(int saleAmount);
   private:
      string name;
      Products products;
};

void Store::ReadAllProducts() {
   products.InputProducts();
}

void Store::PrintSale(int saleAmount) {
   cout << name << "'s sale:" << endl;
   products.PrintAfterDiscount(saleAmount);
}
// New: END Store class

int main() {

   // New: main() now uses Store class
   Store ourPlace;
   string currName;

   cin >> currName;
   ourPlace.SetName(currName);

   ourPlace.ReadAllProducts();
   ourPlace.PrintSale(2);

   return 0;
}
