// Detailed example of compile-time introspection for selecting the largest integer type

#include <type_traits>

// Expand parameter packs to create infinite conjunctions/disjunctions
template <typename... Ts>
using all_integral = std::conjunction<std::is_integral<Ts>...>;

// Implementation universal case
template <bool B, typename...>
struct biggest_int_impl { };

// Implementation base case
template <typename T1, typename T2>
struct biggest_int_impl<true, T1, T2> {
    using type = typename std::conditional<(sizeof(T1) > sizeof(T2)), T1, T2>::type;
};

// Implementation recursive case
template <typename T1, typename T2, typename... Ts>
struct biggest_int_impl<true, T1, T2, Ts...>
    : biggest_int_impl<true, T1, typename biggest_int_impl<true, T2, Ts...>::type>::type { };

// Universal case
template <typename...>
struct biggest_int { };

// Single integer, compare to itself
template <typename T>
struct biggest_int<T> : biggest_int<T, T> { };

// Two integers
template <typename T1, typename T2>
struct biggest_int<T1, T2>
    : biggest_int_impl<all_integral<T1, T2>::value, T1, T2> { };

// More than two integers
template <typename T1, typename T2, typename... Ts>
struct biggest_int<T1, T2, Ts...>
    : biggest_int<T1, typename biggest_int<T2, Ts...>::type> { };

// Interface to the biggest integer type
template <typename... Ts>
using biggest_int_t = typename biggest_int<Ts...>::type;

int run_biggest_integer() {
    biggest_int_t<int> a = 10;
    biggest_int_t<long, char> b = 20;
    biggest_int_t<int, short, long long, char> c = 30;
    static_assert(std::is_same<biggest_int_t<int, short, long long, char>, long long>::value);
    return 0;
}
