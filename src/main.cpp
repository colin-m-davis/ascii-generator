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
  const std::string inpath{argv[1]};
  const std::string outpath{"./build/output"};
  write_asciis(outpath, rgbs_to_asciis((ppm_to_rgbs(inpath))));
  return 0;
}
