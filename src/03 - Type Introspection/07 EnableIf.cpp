// The heart of pre-C++20 metaprogramming: enable_if
// We can use this struct to force substitution failures!

#include <string>

// These definitions exist in the std library!

template <bool B, typename T>
struct enable_if { };

template <typename T>
struct enable_if<true, T> {
    using type = T;
};

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

template <typename T>
typename enable_if<has_to_string<T>::value, std::string>::type func(T t) {
    return t.toString();
}

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

int run_enableif_string() {
    // Substitution failures have been forced
    // IntelliSense detects errors now
    // func(20);
    // func(A { });
    func(B { });
    func(C { });
    // func(D { });
    return 0;
}