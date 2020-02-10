// Generic data structure for an N-sized tuple

#include <cstdlib>
#include <iostream>
#include <string>

// Find element by index
template <std::size_t I, typename T>
struct tuple_element;

// Alias for type of indexed element
template <std::size_t I, typename... Ts>
using tuple_element_t = typename tuple_element<I, Ts...>::type;



// Find element by type
template <typename T, typename Tuple>
struct typed_tuple_element { };



// Universal case
template <typename...>
class tuple;

// Base case, no elements
template <>
class tuple<> {
public:
    constexpr tuple() noexcept { }
};

// Recursive case, N elements
template <typename T, typename... Ts>
class tuple<T, Ts...> : private tuple<Ts...> {
    T data;
public:
    constexpr tuple() : tuple<Ts...>(), data() { }
    constexpr tuple(T first, Ts... rest)
        : tuple<Ts...>(rest...), data(first) { }

    // Allow getters to access private data

    template <std::size_t I, typename... Ts>
    friend constexpr tuple_element_t<I, tuple<Ts...>> &get(tuple<Ts...> &t) noexcept;

    template <typename T, typename... Ts>
    friend constexpr T &get(tuple<Ts...> &t) noexcept;
};



// This template will always return false
// We use it so that static_asserts can be false when type substitution occurs
template <typename>
constexpr bool always_false = false;



// An empty tuple cannot be accessed
template <std::size_t I>
struct tuple_element<I, tuple<>> {
    static_assert(always_false<I>, "tuple index out of bounds");
};

// Base case
template <typename T, typename... Ts>
struct tuple_element<0, tuple<T, Ts...>> {
    using type = T;
    using Ttype = tuple<T, Ts...>;
};

// Recursive case
template <std::size_t I, typename T, typename... Ts>
struct tuple_element<I, tuple<T, Ts...>>
    : tuple_element<I - 1, tuple<Ts...>> { };



// Base case, select this type
template <typename Find, typename... Ts>
struct typed_tuple_element<Find, tuple<Find, Ts...>> {
    // Assure none of the later types are of the same type
    static_assert(!std::disjunction_v<std::is_same<Find, Ts>...>, "duplicate type T in get<T>(tuple)");
    using Ttype = tuple<Find, Ts...>;
};

// Recursive case
template <typename Find, typename T, typename... Ts>
struct typed_tuple_element<Find, tuple<T, Ts...>>
    : typed_tuple_element<Find, tuple<Ts...>> { };



// Get element by index
template <std::size_t I, typename... Ts>
constexpr tuple_element_t<I, tuple<Ts...>> &get(tuple<Ts...> &t) noexcept {
    // static_assert(I < sizeof...(Ts));
    using Ttype = typename tuple_element<I, tuple<Ts...>>::Ttype;
    return static_cast<Ttype &>(t).data;
}

// Get element by type
template <typename T, typename... Ts>
constexpr T &get(tuple<Ts...> &t) noexcept {
    using Ttype = typename typed_tuple_element<T, tuple<Ts...>>::Ttype;
    return static_cast<Ttype &>(t).data;
}



int run_tuple() {
    tuple<int, double, std::string> myTuple { 1, 3.14159, "Hello world!" };
    get<0>(myTuple) = 300;
    get<double>(myTuple) *= 2;
    std::cout << get<0>(myTuple) << std::endl;
    std::cout << get<1>(myTuple) << std::endl;
    std::cout << get<std::string>(myTuple) << std::endl;

    return 0;
}