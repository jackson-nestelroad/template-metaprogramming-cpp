// Example of variadic type parameters

#include <iostream>

namespace console {
    static std::ostream &console = std::cout;

    // Base case
    void log(void) {
        console << std::endl;
    }

    // Recursive case
    template <typename First, typename... Rest>
    void log(const First &first, const Rest &... rest) {
        console << first << ' ';
        log(rest...);
    }
}

int run_variadic() {
    console::log(1, 3.14159, "Hello there!");
    console::log("Variadic parameters can be empty");
    return 0;
}