#include <cstddef>
#include <cstdio>
#include <iostream> 

class Arena {
private:

    std::size_t capacity;
    std::byte*  data;

public:

    Arena(size_t bytes) : capacity(bytes), data(new std::byte[bytes]) {}

    ~Arena() {
        delete[] data;
    }

    size_t size() {
        return capacity;
    }

};