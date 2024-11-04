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
  const std::string frames_dir{argv[1]};
  const std::string outpath{"./build/output"};
  frames_to_asciis(frames_dir);
  return 0;
}
