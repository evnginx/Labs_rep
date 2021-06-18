cmake_minimum_required (VERSION 3.12)


set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project ("CMakeProject1")

# Add source to this project's executable.
add_executable (CMakeProject1 "main.cpp" "1.cpp")

# TODO: Add tests and install targets if needed.
