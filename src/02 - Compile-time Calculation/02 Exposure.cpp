// More modern way to expose types and values in template classes

template <typename T>
struct expose_type {
    using type = T;
};

template <int N>
struct expose_int {
    constexpr static int value = N;
};

int run_exposure() {
    // Type is exposed back as double
    expose_type<double>::type doub = 3.14159;

    // Value is exposed back as a compile-time constant and can be used elsewhere
    int num = expose_int<200>::value;
    return 0;
}