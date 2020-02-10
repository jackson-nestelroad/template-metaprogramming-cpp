// Introduction to C++20 concepts

#include <compare>
#include <concepts>
#include <iostream>

template <typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> bool;
}

template <typename T>
concept EqualityComparable = requires(T a, T b) {
    { a == b } -> bool;
    { a != b } -> bool;
};

template <typename T>
concept TotallyOrdered = requires(T a, T b) {
    { a <=> b } -> std::strong_ordering;
}

template <typename T>
concept Hashable = requires(T a) {
    { std::hash<T>{ }(a) } -> std::convertible_to<std::size_t>;
};

template <Hashable H>
std::size_t hash(const H &data) {
    return std::hash<H> { }(data);
}

struct C {
    int x;
    double y;
};

int run_hashable() {
    std::cout << hash(1.2131) << std::endl;         // Good
    // std::cout << hash(C { 2, 3.14 }) << std::endl;  // Error
    return 0;
}