// Examples of how STL works

#include <string>
#include <vector>
#include <map>

template <typename T>
class vector;

template <typename K, typename V>
class map;

template <typename X, typename Y>
struct pair;

int run_stl() {
    std::vector<int> vec1;
    std::map<int, std::string> map1;

    std::vector<std::vector<double>> vec2;
    std::map<std::string, std::pair<int, double>> map2;

    return 0;
}