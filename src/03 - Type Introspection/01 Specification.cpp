// Showcase how SFINAE works
// Using a specialied template to overcome substitution failures

#include <iostream>

struct foo {
    using type = double;
};

template <typename T>
typename T::type func(const T &t) {
    std::cout << "T::type exists" << std::endl;
    return 0;
}

int func(int t) {
    std::cout << "I am an int" << std::endl;
    return 0;
}

int run_sfinae_specification() {
    func(foo { });  // Called with T = foo
    func(10);       // Called with T = int
                    // int::type does not exist!
                    // Use int func(int)
    return 0;
}