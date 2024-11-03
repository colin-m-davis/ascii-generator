#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct RGB;

auto ppm_to_rgbs(std::ifstream f) -> std::vector<std::vector<RGB>>;
