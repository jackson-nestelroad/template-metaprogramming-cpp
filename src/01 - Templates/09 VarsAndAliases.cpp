// Examples of using template variables and type aliases

#include <iostream>
#include <string>
#include <map>

constexpr long double PI = 3.141592653589793238462643383L;

template <typename T>
T typed_pi = T(PI);

template <>
std::string typed_pi<std::string> = std::to_string(PI);

using coordinate = std::pair<std::size_t, std::size_t>;

template <typename T>
using nested_data_plane = std::map<coordinate, std::map<coordinate, T>>;

int run_varsandaliases() {
    std::cout << typed_pi<int> << std::endl;
    std::cout << typed_pi<float> << std::endl;
    std::cout << typed_pi<std::string> << std::endl;

    nested_data_plane<std::string> plane;
    plane[{ 0, 0 }][{ 0, 0 }] = "Origin";

    return 0;
}