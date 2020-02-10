// Reworking the writable type trait as a C++20 concept
// Look how easy!

#include <concepts>
#include <iostream>

template <typename T>
concept Writable = requires(std::ostream &out, T data) {
    { out << data } -> std::ostream &;
};

namespace console {
    static std::ostream &console = std::cout;

    // Base case
    static void log(void) {
        console << std::endl;
    }

    // Recursive case
    template <Writable First, Writable... Rest>
    void log(const First &first, const Rest &... rest) {
        console << first << ' ';
        log(rest...);
    }
}

struct C { int x; double y; };

int run_writable_concept() {
    console::log("Hello", 0, 3.14159);          // Good
    console::log("World", -1, C { 2, 4.0 });    // Error
    return 0;
}