cmake_minimum_required(VERSION 3.10.0)
project(ascii-generator VERSION 0.1.0 LANGUAGES CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

add_executable(ascii-generator src/main.cpp)
target_compile_options(ascii-generator PRIVATE -Wall -Werror -Wextra -Wshadow -Wpedantic -Wunused -Wnon-virtual-dtor)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
