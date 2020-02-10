// Example of printing prime numbers (efficient)

#include <iostream>

template <int N>
constexpr void print_primes() {
    bool is_not_prime[N] { };

    for (int n = 2; n * n < N; ++n) {
        if (!is_not_prime[n]) {
            for (int m = n * n; m < N; m += n) {
                is_not_prime[m] = true;
            }
        }
    }
    for (int n = 2; n < N; ++n) {
        if (!is_not_prime[n]) {
            std::cout << "Prime: " << n << std::endl;
        }
    }
}

int run_primes_efficient() {
    print_primes<100>();
    return 0;
}