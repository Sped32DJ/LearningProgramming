#include <iostream>
using namespace std;

class Member {
   public:
      int GetAge() const;
		int GetNumPoints() const;
      string GetName() const;
      /* Member function declarations go here */
      void SetAge(int newAge);
      void SetNumPoints(int newNumPoints);
      void SetName(string newName);
   private:
      int age;
      int numPoints;
      string name;
      /* Data members go here */
};

void Member::SetAge(int newAge) {
   age = newAge;
}

void Member::SetNumPoints(int newNumPoints) {
	numPoints = newNumPoints;
}

void Member::SetName(string newName) {
   name = newName;
}

int Member::GetAge() const {
   return age;
}

int Member::GetNumPoints() const {
	return numPoints;
}

string Member::GetName() const {
   return name;
}

int main() {
   Member member1;
   int inputAge;
	int inputNumPoints;
   string inputName;

   cin >> inputAge;
	cin >> inputNumPoints;
   cin >> inputName;

   member1.SetAge(inputAge);
	member1.SetNumPoints(inputNumPoints);
   member1.SetName(inputName);
   cout << "Age: " << member1.GetAge() << endl;
	cout << "Number of points: " << member1.GetNumPoints() << endl;
   cout << "Name: " << member1.GetName() << endl;

   return 0;
}
