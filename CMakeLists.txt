cmake_minimum_required(VERSION 3.10.0)
project(ascii-generator VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost REQUIRED)

add_executable(ascii-generator src/main.cpp)

foreach(ascii-generator)
    target_compile_options(${target} PRIVATE -Wall -Werror -Wextra -Wshadow -Wpedantic -Wunused -Wnon-virtual-dtor)
endforeach()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
