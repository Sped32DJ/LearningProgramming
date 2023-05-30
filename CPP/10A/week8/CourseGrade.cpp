#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

double AverageScore(int mid1, int mid2, int finalscore) {
  return (mid1 + mid2 + finalscore) / 3.0;
}

double ExamAvg(const vector<int> &v) {
  double sum = 0;
  for (size_t i = 0; i < v.size(); ++i) {
    sum += v.at(i);
  }
  return sum / v.size();
}

int main() {
  // variables
  ifstream inputStream;
  ofstream outputStream;
  string name;
  string fileName;
  int score;
  double average;
  vector<string> vLastNames;
  vector<string> vFirstNames;
  vector<int> vMidterm1;
  vector<int> vMidterm2;
  vector<int> vFinal;
  vector<char> vGrade;

  // read file from user and read the tsv file
  cin >> fileName;
  inputStream.open(fileName);

  if (!inputStream.is_open()) {
    cout << "no file ;()" << endl;
    return 0;
  }

  while (inputStream >> name) {
    vLastNames.push_back(name);

    inputStream >> name;
    vFirstNames.push_back(name);

    inputStream >> score;
    vMidterm1.push_back(score);

    inputStream >> score;
    vMidterm2.push_back(score);

    inputStream >> score;
    vFinal.push_back(score);
  }
  inputStream.close(); // always close the file

  outputStream.open("report.txt");

  // For each student
  for (size_t i = 0; i < vFinal.size(); ++i) {
    average = AverageScore(vMidterm1.at(i), vMidterm2.at(i), vFinal.at(i));
    if (average >= 90)
      vGrade.push_back('A');
    else if (average >= 80)
      vGrade.push_back('B');
    else if (average >= 70)
      vGrade.push_back('C');
    else if (average >= 60)
      vGrade.push_back('D');
    else
      vGrade.push_back('F');

    outputStream << vLastNames.at(i) << '\t' << vFirstNames.at(i) << '\t'
                 << vMidterm1.at(i) << '\t' << vMidterm2.at(i) << '\t'
                 << vFinal.at(i) << '\t' << vGrade.at(i) << endl;
  }

  // Put information into report.txt file
  outputStream << endl
               << fixed << setprecision(2) << "Averages: midterm1 "
               << ExamAvg(vMidterm1) << ", midterm2 " << ExamAvg(vMidterm2)
               << ", final " << ExamAvg(vFinal) << endl;

  outputStream.close();
  return 0;
}
