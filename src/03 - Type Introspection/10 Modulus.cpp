// Using metaprogramming to implement discrete mathematics modulus using code generation

// a % b = r
// a = bq + r
// 0 <= r < b

#include <iostream>
#include <numeric>
#include <type_traits>

// Helper traits to decide the signed-ness of integer types

template <typename A, typename B>
using both_signed = std::conjunction<std::is_signed<A>, std::is_signed<B>>;

template <typename A, typename B>
using both_unsigned = std::conjunction<std::is_unsigned<A>, std::is_unsigned<B>>;

template <typename A, typename B>
using first_signed = std::conjunction<std::is_signed<A>, std::is_unsigned<B>>;

template <typename A, typename B>
using second_signed = std::conjunction<std::is_unsigned<A>, std::is_signed<B>>;

template <typename A, typename B>
using mod_result_t = std::make_unsigned_t<std::common_type_t<A, B>>;


// Both positive => use remainder operator untouched
template <typename A, typename B>
constexpr inline typename std::enable_if<std::disjunction<both_unsigned<A, B>>::value, mod_result_t<A, B>>::type
mod(A a, B b) {
    return a % b;
}

// Second may be negative => need to cast signed divisor
template <typename A, typename B>
constexpr inline typename std::enable_if<std::disjunction<second_signed<A, B>>::value, mod_result_t<A, B>>::type
mod(A a, B b) {
    return a % static_cast<std::make_signed_t<B>>(b < 0 ? -b : b);
}

// Both may be negative => check if result is negative
template <typename A, typename B>
constexpr inline typename std::enable_if<both_signed<A, B>::value, mod_result_t<A, B>>::type
mod(A a, B b) {
    auto out = a % b;
    if (out < 0) {
        out += b < 0 ? -b : b;
    }
    return out;
}

// First may be negative => more cases to handle
template <typename A, typename B>
typename std::enable_if<first_signed<A, B>::value, mod_result_t<A, B>>::type
constexpr mod(A a, B b) {
    if (a < 0) {
        // b overflows size of type A
        if (b > static_cast<B>(std::numeric_limits<A>::max())) {
            return b + a;
        }
        return b - (static_cast<std::make_unsigned_t<A>>(-a) % b);
    }
    // Result will be positive
    return static_cast<std::make_unsigned_t<A>>(a) % b;
}

int run_modulus() {
    constexpr auto a1 = 1 % 10;
    constexpr auto a2 = 1 % -10;
    constexpr auto a3 = -1 % 10;
    constexpr auto a4 = -1 % -10;

    constexpr auto b1 = mod(1, 10);
    constexpr auto b2 = mod(1, -10);
    constexpr auto b3 = mod(-1, 10);
    constexpr auto b4 = mod(-1, -10);

    constexpr auto c1 = mod(1ULL, 10ULL);
    constexpr auto c2 = mod(1ULL, -10LL);
    constexpr auto c3 = mod(-1LL, 10ULL);
    constexpr auto c4 = mod(-1LL, -10LL);

    return 0;
}