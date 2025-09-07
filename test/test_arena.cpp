// tests/test_arena.cpp
#define UNIT_TEST 1
#include "../src/arena.cpp"   

#include <cassert>
#include <cstdio>
#include <cstddef>
#include <cstdint>

int main() {
  // basic construct
  Arena a(1024);
  std::puts("[OK] test_arena passed");
}
