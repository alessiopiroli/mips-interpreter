cmake_minimum_required(VERSION 3.22.1)
project(mips-interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_subdirectory(src)
add_subdirectory(src/mips-debugger)