// First possible way to achieve compile-time introspection
// Leveraging the fact that array sizes and sizeof() are calculated at compile-time

#include <iostream>

template <typename T>
struct has_internal_type {
    using yes = char[1];    // sizeof(yes) == 1
    using no = char[2];     // sizeof(no) == 2

    // Use SFINAE to determine if T::type exists
    template <typename T>
    static yes &test(typename T::type *);

    template <typename>
    static no &test(...);

    constexpr static bool value = sizeof(test<T>(0)) == sizeof(yes);
};

struct foo {
    using type = double;
};

int run_has_internal_type() {
    std::cout << has_internal_type<foo>::value << std::endl;    // true
    std::cout << has_internal_type<int>::value << std::endl;    // false
    return 0;
}