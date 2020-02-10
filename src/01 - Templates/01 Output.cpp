// Simple template function example

#include <iostream>
#include <string>

// Generic function to output data to std::cout
// Will generate compile-time error if data type does not define the << operator
template <typename T>
void output(T data) {
    std::cout << data << std::endl;
}

struct node {
    int data;
    node *next;

    // Define the << operator so it can be used by output<node>(node)
    friend std::ostream &operator<<(std::ostream &out, const node &data) {
        out << data.data;
        return out;
    }
};

int run_output() {
    output<double>(3.14159);                // Generates output<double>(double)
    output<>('H');                          // Generates output<char>(char)
    output(20);                             // Generates output<int>(int)
    output("Hello!");                       // Generates output<const char *>(const char *)
    output<std::string>("Hello again!");    // Generates output<std::string>(std::string>)

    node myNode { 1, nullptr };
    output(myNode);                         // Generates output<node>(node)

    return 0;
}