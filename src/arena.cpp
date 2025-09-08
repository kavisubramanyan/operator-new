#include <cstddef>
#include <cstdio>
#include <iostream> 

class Arena {
private:

    std::size_t capacity_;
    std::byte*  data_;

public:

    // constructor/destructor
    Arena(size_t bytes) : capacity_(bytes), data_(new std::byte[bytes]) {}
    ~Arena() {
        delete[] data_;
    }

    // prevent copying
    Arena(const Arena&)             = delete;
    Arena& operator=(const Arena&)  = delete;


    // move semantics
    Arena(Arena&& b) noexcept : capacity_(b.capacity_), data_(b.data_) {
        b.data_ = nullptr;
        b.capacity_ = 0;
    }
    Arena& operator=(Arena&& b) noexcept {
        if(this != &b) {
            delete[] data_;
            data_ = b.data_;
            capacity_ = b.capacity_;
            b.data_ = nullptr;
            b.capacity_ = 0;
        }
        return *this;
    }

    size_t size() const noexcept {
        return capacity_;
    }

    std::byte* base() noexcept {
        return data_;
    }

    const std::byte* base() const noexcept {
        return data_;
    }

    std::byte* end() noexcept {
        return data_+capacity_;
    }

    const std::byte* end() const noexcept {
        return data_+capacity_;
    }

    bool owns(const void* p) const noexcept {
        if(!data_) return false;
        auto loc = static_cast<const std::byte*>(p);
        return loc>=data_ && loc<data_+capacity_;
    }

    void dump() const noexcept {
        std::cout << "Capacity: " << capacity_ << std::endl;
        std::cout << "Base Location: " << base() << std::endl;
    }



};