// Example of non-type parameters

#include <iostream>
#include <stdexcept>

template <typename T, int size>
struct array {
    T data[size];

    T &operator[](int i) {
        if (i < 0 || i >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[i];
    }
};

constexpr std::size_t size = 20;

int run_array() {
    // Explicitly declare constant OR use constexpr
    array<int, 4> intArr { 1, 2, 3, 4 };
    array<int, size> squares;

    for (int i = 0; i < size; ++i) {
        squares[i] = i * i;
        std::cout << squares[i] << ' ';
    }

    // Works in multiple dimensions!
    array<array<std::string, 2>, 2> str2dArr { 
        { { "Hello", "World" }, { "Goodbye", "World" } } 
    };

    return 0;
}