// Example of template specialization for functions

#include <iostream>
#include <string>
#include <functional>

// This function generalizes input validation... but what about strings with whitespace?
template <typename T>
T readUserInput(std::istream &input, std::ostream &output,
    const std::string &prompt, const std::function<bool(const T &)> &validate) {
    T readData;
    while (true) {
        output << prompt;

        if (input >> readData && validate(readData)) {
            return readData;
        }
        else {
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            output << "Invalid input!" << std::endl;
        }
    }
}

// Specialize the function for string type!
template <>
std::string readUserInput<std::string>(std::istream &input, std::ostream &output,
    const std::string &prompt, const std::function<bool(const std::string &)> &validate) {
    std::string readData;
    
    // Ignore current line; we are getting a new one!
    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    while (true) {
        output << prompt;
        // Use getline opposed to >>
        if (std::getline(input, readData) && validate(readData)) {
            return readData;
        }
        else {
            input.clear();
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            output << "Invalid input!" << std::endl;
        }
    }
}

int run_input() {
    auto i = readUserInput<double>(std::cin, std::cout, 
        "Enter a positive double: ", [](auto d) { return d > 0.0; });
    auto d = readUserInput<int>(std::cin, std::cout, 
        "Enter an integer > 100: ", [](auto i) { return i > 100; });
    auto str = readUserInput<std::string>(std::cin, std::cout, 
        "Enter any string: ", [](auto str) { return true; });

    std::cout << "You entered: " << i << ", " << d << ", \"" << str << "\"" << std::endl;
    return 0;
}