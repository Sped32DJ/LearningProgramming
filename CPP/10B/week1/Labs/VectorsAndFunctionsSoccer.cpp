#include <iostream>
#include <vector>
using namespace std;

// parameter order will always be jersey #s then ratings
void outputRoster(const vector<int> &vJers, const vector<int> &vRate);
void addPlayer(vector<int> &vJers, vector<int> &vRate);
void removePlayer(vector<int> &vJers, vector<int> &vRate);
void updatePlayerRating(const vector<int> &vJers, vector<int> &vRate);
void outputPlayersAboveRating(const vector<int> &vJers,
                              const vector<int> &vRate);
int LocateIndex(const vector<int> &vJers, int num);

int main() {
  vector<int> jerseyNums(5);
  vector<int> vRating(5);
  char option;
  size_t value;

  for (size_t i = 0; i < jerseyNums.size(); ++i) {
    cout << "Enter player " << i + 1 << "'s jersey number: ";
    cin >> value;
    cout << endl;
    jerseyNums.at(i) = value;
    cout << "Enter player " << i + 1 << "'s rating: ";
    cin >> value;
    cout << endl;

    vRating.at(i) = value;
    cout << endl;
  }

  outputRoster(jerseyNums, vRating);
  while (option != 'q') {
    cout << "MENU" << endl
         << "a - Add player\n"
         << "d - Remove player\n"
         << "u - Update player rating\n"
         << "r - Output players above a rating\n"
         << "o - Output roster\n"
         << "q - Quit\n"
         << endl
         << "Choose an option: \n";
    cin >> option;
    if (option == 'a') {
      addPlayer(jerseyNums, vRating);
    } else if (option == 'd') {
      removePlayer(jerseyNums, vRating);
    } else if (option == 'u') {
      updatePlayerRating(jerseyNums, vRating);
    } else if (option == 'r') {
      outputPlayersAboveRating(jerseyNums, vRating);
    } else if (option == 'o') {
      outputRoster(jerseyNums, vRating);
    }
  }
  return 0;
}

int LocateIndex(const vector<int> &vJers,
                int num) { // function locates index using Jersey#
  int index;
  for (size_t i = 0; i < vJers.size(); ++i) {
    if (vJers.at(i) == num) {
      index = i;
      i = vJers.size();
    }
  }
  return index;
}

void outputRoster(const vector<int> &vJers, const vector<int> &vRate) {

  cout << "ROSTER" << endl;
  for (size_t i = 0; i < vJers.size(); ++i) {
    cout << "Player " << i + 1 << " -- "
         << "Jersey number: " << vJers.at(i) << ", "
         << "Rating: " << vRate.at(i) << endl;
  }
  cout << endl;
}

void addPlayer(vector<int> &vJers, vector<int> &vRate) {
  int value;
  cout << "Enter another player's jersey number: ";
  cin >> value;
  cout << endl;

  vJers.push_back(value);
  cout << "Enter another player's rating: ";
  cin >> value;
  cout << endl << endl;
  vRate.push_back(value);
}

void removePlayer(vector<int> &vJers, vector<int> &vRate) {
  int value;
  int index;
  cout << "Enter a jersey number: ";
  cin >> value;
  cout << endl << endl;

  index = LocateIndex(vJers, value);

  if (index != -1) {
    vJers.erase(vJers.begin() + index);
    vRate.erase(vRate.begin() + index);
  }
  /* vJers.erase(index);
  vRate.erase(index); */
}

void updatePlayerRating(const vector<int> &vJers, vector<int> &vRate) {
  size_t rating;
  int index;
  cout << "Enter a jersey number: ";
  cin >> index;
  cout << endl;

  index = LocateIndex(vJers, index);

  cout << "Enter a new rating for player: ";
  cin >> rating;
  cout << endl << endl;
  vRate.at(index) = rating;
}

void outputPlayersAboveRating(const vector<int> &vJers,
                              const vector<int> &vRate) {
  int value;
  cout << "Enter a rating: ";
  cin >> value;
  cout << endl << endl;

  cout << "ABOVE " << value << endl;
  for (size_t i = 0; i < vJers.size(); ++i) {
    if (vRate.at(i) > value) {
      cout << "Player " << i + 1 << " -- Jersey number: " << vJers.at(i)
           << ", Rating: " << vRate.at(i) << endl;
    }
  }
  cout << endl;
}
