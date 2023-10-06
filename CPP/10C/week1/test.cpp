#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Employee {
public:
   void SetName(string employeeName) {
      name = employeeName;
   }

   virtual void PrintInfo() {
      cout << name << endl;
   }

protected:
   string name;
};

class Professor : public Employee {
public:
   void SetSubject(string setSubject) {
      subject = setSubject;
   }

   void PrintInfo() {
      cout << name << " teaches " << subject << endl;
   }

private:
   string subject;
};

class Designer : public Employee {
public:
   void SetObject(string setObject) {
      object = setObject;
   }

   void PrintInfo() {
      cout << name << " designs " << object << endl;
   }

private:
   string object;
};

int main() {
   Employee* person1;
   Professor* person2;
   Designer* person3;

   vector<Employee*> personList;
   unsigned int i;

   person1 = new Employee();
   person1->SetName("Mia");

   person2 = new Professor();
   person2->SetName("Liam");
   person2->SetSubject("Statistics");

   person3 = new Designer();
   person3->SetName("Cora");
   person3->SetObject("cars");

   personList.push_back(person1);
   personList.push_back(person2);
   personList.push_back(person3);

   for (i = 0; i < personList.size(); ++i) {
      personList.at(i)->PrintInfo();
   }

   return 0;
}
