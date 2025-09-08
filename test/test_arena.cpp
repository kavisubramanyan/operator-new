// tests/test_arena.cpp
#define UNIT_TEST 1
#include "../src/arena.cpp"   

#include <cassert>
#include <cstdio>
#include <cstddef>
#include <cstdint>

#define CHECK(expr) do { \
	if(!(expr)) { \
		std::fprintf(stderr, "CHECK failed: %s:%d: %s\n", __FILE__, __LINE__, #expr); \
		std::abort(); \
	} \
} while(0)

static void test_basic_construct() {
	Arena a = Arena(1024);
	CHECK(a.size() == 1024);
	CHECK(a.base() != nullptr);
	CHECK(a.end() == a.base() + a.size());
}

static void test_owns() {
	Arena a = Arena(1024);
	CHECK(a.owns(a.base() + 1023));
	CHECK(!a.owns(a.end()));
	CHECK(a.owns(a.base()));
	CHECK(!a.owns(a.base()-1));
}

static void test_move_semantics() {
	Arena a(512);
	auto old_base = a.base();
	auto old_size = a.size();
	Arena b(0);
	b = std::move(a);
	CHECK(a.size() == 0);        
	CHECK(a.base() == nullptr);
	CHECK(b.size() == old_size);
	CHECK(b.base() == old_base);
}


int main() {
	test_basic_construct();
	test_owns();
	test_move_semantics();
	std::puts("[OK] test_arena passed");
}
