// Simulating compile-time square root for integers

#include <cstddef>
#include <numeric>

// Binary search for square root
constexpr std::size_t ct_sqrt(std::size_t N, std::size_t l, std::size_t r) {
    if (l == r) {
        return r;
    }
    const auto mid = (l + r + 1) / 2;
    return (N / mid < mid) ? ct_sqrt(N, l, mid - 1) : ct_sqrt(N, mid, r);
}

constexpr std::size_t ct_sqrt(std::size_t N) {
    return ct_sqrt(N, 0, N / 2 + 1);
}

int run_sqrt() {
    int n = 26;
    n *= n;
    // If a function is optionally constexpr, 
    // you must specify when to use compile-time calculation
    constexpr auto a = ct_sqrt(2147395600);                                 // 46340
    const auto b = ct_sqrt(100);                                            // Runtime calculation
    constexpr auto c = ct_sqrt(std::numeric_limits<std::size_t>::max());    // 4294967296 = 2^32
    auto d = ct_sqrt(n);                                                    // Runtime calculation
    return 0;
}