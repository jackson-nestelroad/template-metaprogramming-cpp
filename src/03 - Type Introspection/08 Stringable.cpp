// Cleaning up our SFINAE implementation with more modern features

#include <iostream>
#include <string>
#include <type_traits>

template <typename T, typename = std::string>
struct has_to_string : std::false_type { };

template <typename T>
struct has_to_string<T, decltype(std::declval<T>().toString())> : std::true_type { };

template <typename T, typename = std::string>
struct can_to_string : std::false_type { };

template <typename T>
struct can_to_string<T, decltype(std::to_string(std::declval<T>()))> : std::true_type { };

// A single common type trait for stringable objects
template <typename T>
using is_stringable = std::disjunction<
    has_to_string<T>,
    can_to_string<T>,
    std::is_convertible<T, std::string>
>;

// Overload func for anything we want!

template <typename T>
typename std::enable_if<has_to_string<T>::value, std::string>::type func(T t) {
    return t.toString();
}

template <typename T>
typename std::enable_if<can_to_string<T>::value, std::string>::type func(T t) {
    return std::to_string(t);
}

template <typename T>
typename std::enable_if<std::is_convertible<T, std::string>::value, std::string>::type func(T t) {
    return t;
}

struct B {
    std::string toString() { return "B"; }
};
struct C {
    std::string toString() const { return "C"; }
};

int run_stringable() {
    std::cout << func(20) << std::endl;
    std::cout << func(B { }) << std::endl;
    std::cout << func(C { }) << std::endl;
    std::cout << func("Hello!") << std::endl;
    return 0;
}