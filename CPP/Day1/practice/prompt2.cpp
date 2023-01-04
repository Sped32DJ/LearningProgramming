#include <iostream>
#include <string>

int main() {
  std::cout << "Yes or no? [Y/n] ";
  std::cin.sync();
  std::string input;
  std::getline(std::cin, input);

  if (input.empty() || input[0] == 'y' || input[0] == 'Y') {
    std::cout << "Hello" << std::endl;
  } else {
    std::cout << "Bye" << std::endl;
  }

  return 0;
}

