// Example of printing prime numbers (inefficient)

#include <iostream>

template <int P, int I>
struct is_prime {
    constexpr static bool value = (P % I) && is_prime<P, I - 1>::value;
};

template <int P>
struct is_prime<P, 1> {
    constexpr static bool value = true;
};

template <int I>
struct prime_print {
    constexpr static bool value = is_prime<I, I - 1>::value;
    static void f() {
        prime_print<I - 1>::f();
        if (value) {
            std::cout << "Prime number: " << I << std::endl;
        }
    }
};

template <>
struct prime_print<1> {
    constexpr static bool value = true;
    static void f() { }
};

int run_primes() {
    prime_print<30>::f();
    return 0;
}