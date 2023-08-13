#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Exam { // creating your own datatype
  string uname;
  int score;
};
int main(int argc, *argv[]) {
  Exam quizScore; // create an object

  quizScore.score = 10;
  quizScore.uname = "Senko San";

  /* cout << quizScore.at(0).score << endl; // Not used because not vector */
  cout << quizScore.score << endl;
  cout << quizScore.uname << endl;

  // =======================================================================

  if (argc != 2) {
    cout << "USAGE: " << argv[0] << " inputfile" << endl;
    return EXIT_FAILURE;
  }
  ifstream fin(argv[1]); // Declares + opens

  if (!fin.is_open()) {
    cout << "Error opening " << argv[1] << endl;
    return EXIT_FAILURE;
  }

  Exam entry;
  vector<Exam> quiz1;

  /* fin >> entry.uname;
  while (entry.uname != "done") {
    fin >> entry.score;
    quiz1.push_back(entry);
    fin >> entry.uname;
  } */

  // Better way to write this
  while (fin >> entry.uname >> entry.score) {
    quiz1.push_back(entry);
  }

  cout << quiz1.at(0).uname << ' ' << quiz1.at(0).score << endl;

  return 0;
}
