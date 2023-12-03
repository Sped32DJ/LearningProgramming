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

  vector<int> calibration_vals;
  while (getline(file, line)) {
    vector<int> digits;
    for (size_t i = 0; i < line.size(); ++i) {
      const auto c = line[i];
      if (isdigit(c)) {
        digits.push_back(c - '0');
      }
    }
    calibration_vals.push_back(digits[0] * 10 + digits.back());
  }

  const auto sum = std::accumulate(std::begin(calibration_vals),
                                   std::end(calibration_vals), 0);
  cout << sum << endl;

  return 0;
}
