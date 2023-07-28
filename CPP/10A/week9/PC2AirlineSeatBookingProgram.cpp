/*Spring2023 - PA #2*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Function displays menu options
void DisplayMenu() {
  cout << "Menu options:" << endl
       << "1. Display All Seats Status:" << endl
       << "2. Total Number of Available Seats:" << endl
       << "3. Display Available Seats: " << endl
       << "4. Book Seat:" << endl
       << "5. Cancel Seat:" << endl
       << "6. Change Seat:" << endl
       << "7. Quit:" << endl
       << endl
       << "Please select an option: " << endl;
}

// Function should show all seats and seat status where a 0 marks the seat
// status as available and an 1 marks the seat status as occupied.
void DisplayAllSeatsStatus(const vector<string> &v, const vector<bool> &taken) {
  cout << endl << "Seat\tStatus" << endl;
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v.at(i) << '\t' << taken.at(i) << endl;
  }
  cout << endl;
}

// Function should show the number of seats not currently booked
int TotalNumberOfAvailableSeats(const vector<bool> &taken) {
  size_t count = 0;
  for (size_t i = 0; i < taken.size(); ++i) {
    if (taken.at(i) == false) {
      ++count;
    }
  }
  return count;
}

// Function display which seats are currently available
// TODO (Left side of book works)
void DisplayAvailableSeats(const vector<string> &v, const vector<bool> &taken) {

  for (size_t i = 0; i < v.size(); ++i) {
    if (taken.at(i) == false) {
      cout << v.at(i) << endl;
    }
  }
  cout << endl;
}

// Function should take in a seat from user and mark that seat as unavailable
void BookSeat(const string &seatName, const vector<string> &v,
              vector<bool> &taken) {

  // Index of seat
  size_t index;
  for (size_t i = 0; i < v.size(); ++i) {
    if (v.at(i) == seatName) {
      index = i;
      i = v.size();
    }
  }

  // Check if already booked
  if (taken.at(index) == true) {
    /* cout << "seat " << seatName << " is already booked." << endl; */
    cout << "That seat is already taken.";
  }

  // book the seat
  taken.at(index) = true;

  cout << endl << "Enter seat to book: " << endl;
  cout << endl << "Seat\tStatus" << endl;
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v.at(i) << '\t' << taken.at(i) << endl;
  }
  cout << endl;
}

// Function should take in a seat from user and mark that seat as available
void CancelSeat(const string &seatName, const vector<string> &v,
                vector<bool> &taken) {
  size_t cancelIndex;

  for (size_t i = 0; i < v.size(); ++i) {
    if (v.at(i) == seatName) {
      cancelIndex = i;
      i = v.size();
    }
  }

  if (taken.at(cancelIndex) == false) {
    cout << "Seat " << seatName << " is already available." << endl;
  }

  taken.at(cancelIndex) = false;
}

// Function should take in two seats from the user.  It should mark the first
// seat as available and the second seat as unavailable
void ChangeSeat(const string &cancelSeat, const string &bookSeat,
                const vector<string> &v, vector<bool> &taken) {

  size_t cancelIndex;
  size_t bookIndex;

  for (size_t i = 0; i < v.size(); ++i) {
    if (v.at(i) == cancelSeat) {
      cancelIndex = i;
      i = v.size();
    }
  }

  if (taken.at(cancelIndex) == false) {
    cout << "Seat " << cancelSeat << " is already available." << endl;
  }

  // cancel seat
  taken.at(cancelIndex) = false;

  // Find index of booked seat
  for (size_t i = 0; i < v.size(); ++i) {
    if (v.at(i) == bookSeat) {
      bookIndex = i;
      i = v.size();
    }
  }

  // Check if seat already booked
  if (taken.at(bookIndex) == true) {
    cout << "Seat " << bookSeat << " is already booked." << endl;
    taken.at(cancelIndex) = true;
  }

  // book seat
  taken.at(bookIndex) = true;

  // Display update
  cout << endl << "Seat\tStatus" << endl;
  for (size_t i = 0; i < v.size(); ++i) {
    cout << v.at(i) << '\t' << taken.at(i) << endl;
  }
  cout << endl;
}

/* void ChangeSeat(const string &cancelSeat, const string &Column,
                const vector<string> &v, const vector<string> &h,
                vector<bool> &taken) {

} */

// add other functions you might need here

int main() {
  vector<string> seats;
  vector<bool> taken(25, false);
  int ans;
  /* string row; */
  /* string column; */
  string cancelSeat;
  string bookseat; // All lowercase is the string
  string seatName;

  // Filling up the vector
  for (size_t row = 0; row < 5; ++row) {
    for (char col = 'A'; col <= 'E'; ++col) {
      string seat = to_string(row + 1) + col;
      seats.push_back(seat);
    }
  }

  DisplayMenu();

  cin >> ans;
  while (ans < 7) {
    if (ans == 1) {
      DisplayAllSeatsStatus(seats, taken);
      DisplayMenu();
    } else if (ans == 2) {
      cout << endl
           << "Number of available seats: "
           << TotalNumberOfAvailableSeats(taken) << endl
           << endl;
    } else if (ans == 3) {
      cout << endl << "Available seats:" << endl;
      DisplayAvailableSeats(seats, taken);
    } else if (ans == 4) {
      cin >> seatName;
      BookSeat(seatName, seats, taken);
    } else if (ans == 5) {
      cout << "Enter seat to cancel" << endl;
      cin >> seatName;
      CancelSeat(seatName, seats, taken);
    } else if (ans == 6) {
      cout << "Enter seat to cancel: " << endl;
      cin >> cancelSeat;
      cout << "Enter seat to book: " << endl;
      cin >> bookseat;
      cin >> seatName;
      ChangeSeat(cancelSeat, bookseat, seats, taken);
    }
    DisplayMenu();
    cin >> ans;
  }
  cout << endl;

  return 0;
}
