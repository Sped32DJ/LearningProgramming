#include <iostream>
using namespace std;

string getDayofWeek(int dayNum) {
  string dayName;

  /*  if(dayNum == 0){
        dayName == "Sunday";
    } else if(dayNum == 1){
        dayName == "monday";
    } */
  switch (dayNum) {
  case 0:
    dayName = "Sunday";
    break;
  case 1:
    dayName = "Monday";
    break;
  case 2:
    dayName = "Tuesday";
    break;
  case 3:
    dayName = "Wenesday";
    break;
  case 4:
    dayName = "Thursday";
    break;
  case 5:
    dayName = "Friday";
    break;
  case 6:
    dayName = "Saturday";
    break;
  default:
    dayName = "Invalid";
  }

  return dayName;
}

int main() {
  cout << "It is " << getDayofWeek(0) << endl;
  return 0;
}

/* Practice: What day of the week is it
odd week days = 31 days
even = 30
Feb = 28 */
