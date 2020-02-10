// Original ways to expose types and values in template classes

template <typename T>
struct expose_type {
    typedef T type;
};

template <int N>
struct expose_int {
    enum { value = N };
};

int run_exposure_old() {
    // Type is exposed back as double
    expose_type<double>::type doub = 3.14159;

    // Value is exposed back as a compile-time constant and can be used elsewhere
    int num = expose_int<200>::value;
    return 0;
}