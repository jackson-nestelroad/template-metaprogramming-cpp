#include <string>

template <typename T, T t>
struct have_equal_types { };

template <typename T>
struct has_to_string {
    using yes = char[1];
    using no = char[2];

    template <typename T>
    static yes &test(have_equal_types<std::string(T::*)(), &T::toString> *);

    template <typename T>
    static yes &test(have_equal_types<std::string(T::*)() const, &T::toString> *);

    template <typename>
    static no &test(...);

    constexpr static bool value = sizeof(test<T>(0)) == sizeof(yes);
};

struct A { };

struct B {
    std::string toString() { return "B"; }
};

struct C {
    std::string toString() const { return "C"; };
};

struct D {
    char toString() { return 'D'; };
};

int run_has_tostring() {
    has_to_string<int>::value;  // false
    has_to_string<A>::value;    // false
    has_to_string<B>::value;    // true
    has_to_string<C>::value;    // true
    has_to_string<D>::value;    // false
    return 0;
}