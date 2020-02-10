// Shows an error in calling an undefined operation in template substitution

#include <string>

template <typename T>
std::string func(const T &t) {
    return t.toString();
}

// Sink-hole
void func(...);

int run_sfinae_function_error() {
    // func(10);       // Sink-hole is never considered!
    return 0;
}