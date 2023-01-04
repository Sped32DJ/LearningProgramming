#include <algorithm>
#include <iostream>

int main() {
  std::cout << "Enter a number: ";
  std::string input;
  std::getline(std::cin, input);
  input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

  if (input.empty() || input[0] == 'y' || input[0] == 'Y') {
    std::cout << "Hello" << std::endl;
  } else {
    std::cout << "Bye" << std::endl;
  }
  return 0;
}
