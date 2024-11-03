#include "transform.cpp"
#include <fstream>
#include <iostream>
#include <string>

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    std::cerr << "Expected one argument.\n";
    std::cerr << "Usage: " << argv[0] << " <arg>\n";
    return 1;
  }
  const std::string path{argv[1]};
  std::ifstream file{path};
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << path << '\n';
    return 1;
  }
  std::cout << path << '\n';
  const std::string out_path{"./build/output"};
  std::ofstream out_file{out_path};
  out_file << "Hello, world!";
  return 0;
}
