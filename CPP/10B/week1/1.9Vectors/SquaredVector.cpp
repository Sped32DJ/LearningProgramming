#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
#include <cmath>

void SquareVector(vector<double> &vNum, vector<double>& pwr){
   for(size_t i = 0; i < vNum.size(); ++i) {
       pwr.push_back(pow(vNum.at(i), 2));
   }
}

int main() {
   int i;
	vector<double> inputVector;
	int size;
	double input;
	vector<double> squared;

	cin >> size;
	for (i = 0; i < size; ++i) {
		cin >> input;
		inputVector.push_back(input);
	}

   SquareVector(inputVector, squared);

	for (i = 0; i < squared.size(); ++i) {
		cout << fixed << setprecision(2) << squared.at(i) << endl;
	}

   return 0;
}
