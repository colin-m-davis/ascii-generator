#include "transform.hpp"
#include <algorithm>
#include <cassert>
#include <filesystem>
#include <optional>
#include <thread>

const int MAX_COLOR = 255;
const std::string ASCII_CHARACTERS = " .:-=+*abcdefg#%0@";
// const std::string ASCII_CHARACTERS =
//     " `.-':_,^=;><+!rc*/"
//     "z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

template <typename Pixel> struct Image {
  int width;
  int height;
  std::vector<Pixel> pixels;

  std::optional<Pixel> at(int y, int x) const {
    if (y >= 0 && y < height && x >= 0 && x < width) {
      const int index = y * width + x;
      return pixels[index];
    } else {
      return std::nullopt;
    }
  }
};

struct Rgb {
  unsigned char r, g, b;
};

auto ppm_file_to_rgb_image(const auto& inpath) -> std::optional<Image<Rgb>> {
  std::ifstream infile(inpath, std::ios::binary);
  if (!infile.is_open()) {
    return std::nullopt;
  }
  std::string magic_number;
  int width, height, max_color_value;
  infile >> magic_number >> width >> height >> max_color_value;
  infile.ignore(1);
  std::vector<Rgb> pixels(width * height);
  infile.read(reinterpret_cast<char*>(pixels.data()), pixels.size() * 3);
  return Image<Rgb>{width, height, pixels};
}

auto n_to_ascii(const int n) -> unsigned char {
  const int index = std::min(n / ((MAX_COLOR + 1) / ASCII_CHARACTERS.length()),
                             ASCII_CHARACTERS.length() - 1);
  return ASCII_CHARACTERS[index];
}

auto rgb_image_to_ascii_image(const Image<Rgb>& image) -> Image<unsigned char> {
  const auto [width, height, _] = image;

  std::vector<unsigned char> pixels;
  pixels.reserve(width * height);
  for (auto y = 0; y < height; ++y) {
    for (auto x = 0; x < width; ++x) {
      int count_of_nearby = 0;
      int sum_of_nearby_averages = 0;
      for (auto dy = -1; dy <= 1; ++dy) {
        for (auto dx = -1; dx <= 1; ++dx) {
          const auto near_y{y + dy}, near_x{x + dx};
          if (auto pixel = image.at(near_y, near_x)) {
            const auto [r, g, b] = *pixel;
            const auto average = (r + g + b) / 3;
            ++count_of_nearby;
            sum_of_nearby_averages += average;
          }
        }
      }
      const int average_of_averages = sum_of_nearby_averages / count_of_nearby;
      const auto ch = n_to_ascii(average_of_averages);
      pixels.push_back(ch);
    }
  }
  return {width, height, pixels};
}

const int SHRINKER = 4;

auto write_ascii_image(const Image<unsigned char>& image) -> void {
  const auto& [width, height, pixels] = image;
  std::cout << "\033[2J\033[H";
  for (auto y = 0; y < height; y += SHRINKER) {
    for (auto x = 0; x < width; x += SHRINKER) {
      std::cout << image.at(y, x).value_or(ASCII_CHARACTERS[0]) << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::flush;
}

auto frames_to_asciis(const auto& frames_dir) -> void {
  std::vector<std::filesystem::directory_entry> entries;
  for (const auto& entry : std::filesystem::directory_iterator(frames_dir)) {
    entries.push_back(entry);
  }
  std::sort(entries.begin(), entries.end(), [](const auto& a, const auto& b) {
    return a.path().filename() < b.path().filename();
  });
  for (const auto& entry : entries) {
    if (auto image = ppm_file_to_rgb_image(entry.path())) {
      write_ascii_image(rgb_image_to_ascii_image(*image));
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }
}
