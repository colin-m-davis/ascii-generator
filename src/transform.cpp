#include "transform.hpp"
#include <cassert>

const int MAX_COLOR = 255;
const std::string ASCII_CHARACTERS = " .:-=+*#%@";

struct RGB {
  int r;
  int g;
  int b;
};

auto ppm_to_rgbs(const auto& inpath) -> std::vector<std::vector<RGB>> {
  std::ifstream infile{inpath};
  if (!infile.is_open()) {
    throw std::invalid_argument("Error opening file: " + inpath);
  }
  std::string magic_number;
  int width, height, max_color;
  infile >> magic_number;
  infile.get();
  infile >> width >> height;
  infile.get();
  infile >> max_color;
  infile.get();
  std::cout << magic_number << " "
            << " " << width << " " << height << " " << max_color << '\n';
  assert(("Max color must be 255", max_color == MAX_COLOR));
  std::vector<std::vector<RGB>> rows;
  rows.reserve(height);
  for (int y = 0; y < height; ++y) {
    std::vector<RGB> row;
    row.reserve(width);
    for (int x = 0; x < width; ++x) {
      int r, g, b;
      infile >> r >> g >> b;
      const RGB rgb{r, g, b};
      std::cout << rgb.r << '\n';
      row.push_back(rgb);
    }
    rows.push_back(std::move(row));
  }
  return rows;
}

auto is_in_bounds(int height, int width, int y, int x) -> bool {
  return y > 0 && y < height && x > 0 && x < width;
}

auto n_to_ascii(const int n) -> char {
  const int index = n >> 5;
  return ASCII_CHARACTERS[index];
}

auto rgbs_to_asciis(const std::vector<std::vector<RGB>>& rows)
    -> std::vector<std::vector<char>> {
  const int height = rows.size();
  assert(("Height must be positive!", height > 0));
  const int width = rows[0].size();
  assert(("Width must be positive!", width > 0));

  std::vector<std::vector<char>> output;
  output.reserve(height);
  for (int y = 0; y < height; ++y) {
    std::vector<char> row;
    row.reserve(width);
    for (int x = 0; x < height; ++x) {
      int count_of_nearby = 0;
      int sum_of_nearby_averages = 0;
      for (int dy = -1; dy <= 1; ++dy) {
        for (int dx = -1; dx <= 1; ++dx) {
          const int near_y{y + dx}, near_x{x + dx};
          if (!is_in_bounds(height, width, near_y, near_x)) {
            continue;
          }
          auto rgb = rows[near_y][near_x];
          const int average = (rgb.r + rgb.b + rgb.g) / 3;
          ++count_of_nearby;
          sum_of_nearby_averages += average;
        }
      }
      const int average_of_averages = sum_of_nearby_averages / count_of_nearby;
      const auto ch = n_to_ascii(average_of_averages);
      row.push_back(ch);
    }
    output.push_back(std::move(row));
  }
  return {};
}

auto write_asciis(const auto& outpath,
                  const std::vector<std::vector<char>>& asciis) -> void {
  std::ofstream outfile{outpath};
  if (!outfile.is_open()) {
    throw std::invalid_argument("Error opening file: " + outpath);
  }
  for (const auto& row : asciis) {
    for (auto ch : row) {
      std::cout << ch;
      outfile << ch;
    }
    std::cout << '\n';
    outfile << '\n';
  }
}
