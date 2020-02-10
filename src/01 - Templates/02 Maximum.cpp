// Another simple template function example

#include <iostream>
#include <string>

// Generic function to get the maximum out of two values
template <typename T>
T max(const T &a, const T &b) {
    return a < b ? b : a;
}

int run_max() {
    std::cout << "max(1,5) = " << max(1, 5) << std::endl;
    std::cout << "max('a','z') = " << max('a', 'z') << std::endl;
    std::cout << "max(\"Hello\", \"World\") = " << max<std::string>("Hello", "World") << std::endl;

    return 0;
}