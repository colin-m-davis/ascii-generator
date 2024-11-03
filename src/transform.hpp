#pragma once

#include <fstream>
#include <string>
#include <vector>

auto ppm_to_ascii(std::ifstream f) -> std::vector<std::string>;
