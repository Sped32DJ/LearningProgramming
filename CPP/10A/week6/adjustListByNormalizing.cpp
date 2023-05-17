#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {

  int size;
  cin >> size;
  vector<double> vlist;
  double input;
  double max = 0;

  // find max
  for(int i = 0; i < size; ++i){
      cin >> input;
      vlist.push_back(input);
      if(input > max){
          max = input;
      }
  }

  // dividing the vector by the max
  for (int i = 0; i < size; ++i) {
      cout << fixed << setprecision(2);
      cout << vlist.at(i) / max << ' ';
  }
  cout << endl;

  return 0;
}
