// Using a sink-hole function to overcome substitution failures

#include <iostream>

struct foo {
    using type = double;
};

template <typename T>
typename T::type func(const T &t) {
    std::cout << "T::type exists" << std::endl;
    return 0;
}

// Sink-hole
void func(...) { }

int run_sfinae_sinkhole() {
    func(foo { });  // Called with T = foo
    func(10);       // Called with T = int
                    // int::type does not exist!
                    // Use void func(...)
    return 0;
}