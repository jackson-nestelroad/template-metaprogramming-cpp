// Example of constexpr function recursion (C++14)

// Option 1: function template (compile-time only)
template <int N>
constexpr long long factorial_1() {
    static_assert(N >= 0, "Cannot take factorial of negative number");
    if constexpr (N > 1) {
        return N * factorial_1<N - 1>();
    }
    return 1;
}

// Option 2: constexpr function (compile-time or run-time)
constexpr long long factorial_2(int N) {
    return N > 1 ? N * factorial_2(N - 1) : 1;
}

// Option 3: normal function (run-time, but might get lucky and get compile-time)
long long factorial_3(int N) {
    return N > 1 ? N * factorial_3(N - 1) : 1;
}

int run_factorial_functions() {
    int var = 9;
    ++var;

    constexpr auto a = factorial_1<10>();   // Compile-time
    constexpr auto b = factorial_2(10);     // Compile-time
    const auto c = factorial_2(var);        // Run-time
    const auto d = factorial_3(10);         // Run-time (?)
    return 0;
}