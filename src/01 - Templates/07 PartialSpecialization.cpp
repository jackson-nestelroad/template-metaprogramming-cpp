// Example of partial specialization for class templates

#include <iostream>

// Base template MUST be at the top 
template <typename X, typename Y, int I>
struct special {
    void run() { std::cout << "Base template" << std::endl; }
};

template <typename X, int I>
struct special<X, X *, I> {
    void run() { std::cout << "Partial specialization 1" << std::endl; }
};

template <typename X, int I>
struct special<const X &, X, I> {
    void run() { std::cout << "Partial specialization 2" << std::endl; }
};

template <typename X, typename Y>
struct special<X, Y, 10> {
    void run() { std::cout << "Partial specialization 3" << std::endl; }
};

template <>
struct special<int, double, 2020> {
    void run() { std::cout << "Partial specialization 4" << std::endl; }
};

int run_specialization() {
    // Follow the formats above to activate specializations
    special<char, long long, 1> a;
    special<char, char *, 2> b;
    special<const float &, float, 5> c;
    special<double, int, 10> d;
    special<int, double, 2020> e;

    a.run(); b.run(); c.run(); d.run(); e.run();
    return 0;
}