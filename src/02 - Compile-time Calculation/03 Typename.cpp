// Example on the use of the typename keyword with dependent type names

struct bar_as_type {
    using bar = int;
};

struct bar_as_val {
    constexpr static int bar = 200;
};

template <typename T>
void show_dependent_names() {
    // T::bar x;               // is bar a type or a value?

    typename T::bar y;      // bar is a type
}

int run_typename() {
    // We can call with both of these!
    show_dependent_names<bar_as_type>();
    // show_dependent_names<bar_as_val>();      // This no longer compiles when using typename
    return 0;
}