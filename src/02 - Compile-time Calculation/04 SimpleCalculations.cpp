// Examples of simple calculations on compile-time constants

// Compiler is able to carry out these operations since they are using constants
constexpr int A = 10 * 2;           // 20
constexpr int B = 1 << 10;          // 1024
constexpr int C = 5 + 2;            // 7
constexpr int D = (A + B) << C;     // 133632

// So... we can do the same thing with templates!

// These examples are just showcasing compile-time calculations with templates
// They are definitely overkill, but they highlight the basic concept

template <int A, int B>
struct add {
    constexpr static int value = A + B;
};

template <int A, int B>
struct multiply {
    constexpr static int value = A * B;
};

template <int A, int B>
struct left_shift {
    constexpr static int value = A << B;
};

template <int N>
struct power_of_2 : left_shift<1, N> { };

int run_simplecalculations() {
    constexpr int A = multiply<10, 2>::value;
    constexpr int B = power_of_2<10>::value;
    constexpr int C = add<5, 2>::value;
    constexpr int D = left_shift<add<A, B>::value, C>::value;

    return 0;
}