// Example of creating and using an is_writable type trait

#include <iostream>

// Direct SFINAE implementation (long!)
template <typename T>
struct is_writable_verbose {
    template <typename T>
    constexpr static auto test(T *) -> decltype(std::declval<std::ostream &>() << std::declval<T>());
    constexpr static auto test(...) -> std::false_type;

    using result_type = decltype(test(std::declval<T *>()));
    using type = typename std::is_same<std::ostream &, result_type>::type;
    constexpr static bool value = type::value;
};

// Simpler construct

// False case
template <typename T, typename = std::ostream &>
struct is_writable : std::false_type { };

// True case
template <typename T>
struct is_writable<T, decltype(std::declval<std::ostream &>() << std::declval<T>())>
    : std::true_type { };

template <typename... Ts>
using all_writable = std::conjunction<is_writable<Ts>...>;

namespace console {
    static std::ostream &console = std::cout;

    // Base case
    static void log(void) {
        console << std::endl;
    }

    // Must check if ALL are writable if we want the substitution to fail
    // Recursive case
    template <typename First, typename... Rest>
    std::enable_if_t<all_writable<First, Rest...>::value, void>
    log(const First &first, const Rest &... rest) {
        console << first << ' ';
        log(rest...);
    }
}

struct C { int x; double y; };

int run_writable() {
    console::log("Hello", 0, 3.14159);          // Good
    // console::log("World", -1, C { 2, 4.0 });    // Substitution fails
    return 0;
}