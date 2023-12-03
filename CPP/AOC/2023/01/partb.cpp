#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
  string input = "Day1.txt";
  if (argc > 1) {
    input = argv[1];
  }

  string line;
  fstream file(input);

  vector<string> numbers{"one", "two",   "three", "four", "five",
                         "six", "seven", "eight", "nine"};

  vector<int> calibration_vals;

  while (getline(file, line)) {
    vector<int> digits;
    for (size_t i = 0; i < line.size(); ++i) {
      const auto c = line[i];
      if (isdigit(c)) {
        digits.push_back(c - '0');
      }
      for (size_t j = 0; j < numbers.size(); ++j) {
        const auto &n = numbers[j];
        if (line.size() >= i + n.size()) {
          if (line.substr(i, n.size()) == n) {
            digits.push_back(j + 1);
          }
        }
      }
    }
    calibration_vals.push_back(digits[0] * 10 + digits.back());
  }

  const auto sum =
      accumulate(begin(calibration_vals), end(calibration_vals), 0);
  cout << sum << endl;

  return 0;
}
