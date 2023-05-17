#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  const int ROCK = 0;
  const int PAPER = 1;
  const int SCISSORS = 2;
  string name1, name2;

  int seed;
  int rounds;
  int wins1 = 0;
  int wins2 = 0;
  cin >> seed;
  cin >> name1 >> name2;
  cin >> rounds;
  srand(seed); // random seed
  vector<int> move1;
  vector<int> move2;

  while (rounds < 0) { // step 1; rounds
    cout << "Rounds must be > 0" << endl;
    cin >> rounds;
  }

  cout << name1 << " vs " << name2 << " for " << rounds << " rounds" << endl;

  // game logic

  // Fill values into a vector in a while loop until someone wins
  // Final output

  // simple logic
  for (int i = 0; i < rounds; ++i) {
    move1.push_back(rand() % 3);
    move2.push_back(rand() % 3);
    if (move1.at(i) == move2.at(i)) {
      cout << "Tie";
      ++rounds;
    } else if (move1.at(i) == ROCK && move2.at(i) == SCISSORS) {
      cout << name1 << " wins with rock";
      ++wins1;
    } else if (move1.at(i) == SCISSORS && move2.at(i) == ROCK) {
      cout << name2 << " wins with rock";
      ++wins2;
    } else if (move1.at(i) == ROCK && move2.at(i) == PAPER) {
      cout << name2 << " wins with paper";
      ++wins2;
    } else if (move1.at(i) == SCISSORS && move2.at(i) == PAPER) {
      cout << name1 << " wins with scissors";
      ++wins1;
    } else if (move1.at(i) == PAPER && move2.at(i) == SCISSORS) {
      cout << name2 << " wins with scissors";
      ++wins2;
    } else if (move1.at(i) == PAPER && move2.at(i) == ROCK) {
      cout << name1 << " wins with paper";
      ++wins1;
    }
    cout << endl;
  }
  cout << name1 << " wins " << wins1 << " and " << name2 << " wins " << wins2
       << endl;

  // Compare vectors and see who wins (good logic)
  // (This doesn't seem efficient)
  /* if (move1.at(i) == ROCK && move2.at(i) == SCISSORS) {
    cout << name1 << " wins with rock";
  } else if (move1.at(i) == SCISSORS && move2.at(i) == ROCK) {
    cout << name2 << " wins with rock";
  } else if (move1.at(i) == ROCK && move2.at(i) == PAPER) {
    cout << name2 << " wins with paper";
  } else if (move1.at(i) == SCISSORS && move2.at(i) == PAPER) {
    cout << name1 << " wins with scissors";
  } else if (move1.at(i) == PAPER && move2.at(i) == SCISSORS) {
    cout << name2 << " wins with scissors";
  } else if (move1.at(i) == PAPER && move2.at(i) == ROCK) {
    cout << name1 << " wins with paper";
  }
  cout << endl; */

  // cout << {name} wins with {move}
  // rand() % 3 ; // generate 0 - 2 (3 possible values)
  return 0;
}
