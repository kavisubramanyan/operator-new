cmake_minimum_required(VERSION 3.16)
project(allocator CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra)
endif()

# Sanitizers in Debug builds (Linux/macOS clang/g++)
if (CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
  add_compile_options(-fsanitize=address,undefined -O0 -g)
  add_link_options(-fsanitize=address,undefined)
endif()

# --- Tests ---
enable_testing()

add_executable(test_arena test/test_arena.cpp)
add_test(NAME test_arena COMMAND test_arena)

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER}")
