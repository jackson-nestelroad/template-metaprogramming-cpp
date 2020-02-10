// Shows an error in using the addition operator with templates

struct foo {
    using type = double;
};

template <typename T>
T addTwo(const T &t) {
    return t + 2;
}

// Sink-hole
void addTwo(...) { }

int run_sfinae_addition_error() {
    // Both substitutions succeed
    // No IntelliSense errors!
    addTwo(2);
    // addTwo(foo { });    // No operator defined
                        // Sink-hole is never considered!
    return 0;
}