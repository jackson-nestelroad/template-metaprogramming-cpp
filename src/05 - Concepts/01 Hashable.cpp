// Introduction to C++20 concepts

#include <compare>
#include <concepts>
#include <iostream>

template <typename T>
concept Sortable = requires(T a, T b) {
    { a < b } -> std::convertible_to<bool>;
};

template <typename T>
concept EqualityComparable = requires(T a, T b) {
    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

template <typename T>
concept TotallyOrdered = requires(T a, T b) {
    { a <=> b } -> std::convertible_to<std::strong_ordering>;
};

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

struct CustomHashObject {
    int a;
};

namespace std {
    template <>
    struct hash<CustomHashObject> {
        std::size_t operator()(const CustomHashObject &obj) const {
            return hash<int>{ }(obj.a);
        }
    };
}

int run_hashable_concepts() {
    std::cout << hash(1.2131) << std::endl;                     // Good
    // std::cout << hash(C { 2, 3.14 }) << std::endl;              // Error
    std::cout << hash(CustomHashObject { 23 }) << std::endl;    // Good
    return 0;
}