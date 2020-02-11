// Small library for reading input according to types and delimiters

#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace in {
    using file_ptr_stream = std::unique_ptr<std::istream>;



    // Thin wrapper around a single piece of data
    template <typename T>
    struct wrapper {
        T data;
        wrapper() : data() { }
        wrapper(const wrapper &line) = default;
        inline wrapper &operator=(const wrapper &line) = default;
        inline operator T() const { return data; }
        using wrapped_type = T;
    };



    // Receive a single value of input data
    template <typename T, char delim = 0>
    struct value : wrapper<T> {
        friend std::istream &operator>>(std::istream &input, value<T, delim> &value) {
            if (!(input >> value.data)) {
                return input;
            }
            if (input.peek() == delim) {
                input.ignore();
            }
            else {
                input.clear();
            }
            return input;
        }
    };

    // Specialization for no delimiter given
    template <typename T>
    struct value<T, 0> : wrapper<T> {
        friend std::istream &operator>>(std::istream &input, value<T, 0> &value) {
            input >> value.data;
            return input;
        }
    };



    // Receive a single line of input data
    template <typename T = std::string, char delim = '\n'>
    struct line;

    // Specialization for std::string, requires std::getline to get full line
    // Can produce a new stream to parse values from
    template <char delim>
    struct line<std::string, delim> : wrapper<std::string> {
        friend std::istream &operator>>(std::istream &in, line<std::string, delim> &line) {
            std::getline(in, line.data, delim);
            return in;
        }

        operator file_ptr_stream() const {
            return file_ptr_stream(new std::stringstream(data));
        }
    };



    // All type_traits are in this namespace
    namespace {
        // Type trait for if Derived derives from Base<Ts...> for any Ts
        template <template <typename...> typename Base, typename Derived>
        struct is_base_of_template {
            template <typename... Ts>
            constexpr static std::true_type test(Base<Ts...> *);
            constexpr static std::false_type test(...);

            using type = decltype(test(std::declval<Derived *>()));
            constexpr static bool value = std::is_same<type, std::true_type>::value;
        };



        // Checks if T derives from wrapper
        template <typename T>
        using is_wrapper = is_base_of_template<wrapper, T>;

        // Checks if all Ts derive from wrapper
        template <typename... Ts>
        using all_wrappers = std::conjunction<is_wrapper<Ts>...>;



        // Checks if T can be converted to an input stream
        template <typename T>
        using is_streamable = std::is_convertible<T, file_ptr_stream>;

        // Checks if all types are streamable, universal case
        template <typename...>
        struct all_streamable 
            : std::false_type { };

        // Checks if last type is streamable, base case
        // Last type actually does not need to be streamable to work, so always return true
        template <typename T>
        struct all_streamable<T>
            : std::true_type { };

        // Checks if all types are streamable, recursive case
        template <typename T, typename... Ts>
        struct all_streamable<T, Ts...>
            : std::conjunction<is_streamable<T>, all_streamable<Ts...>> { };



        // Checks if a type is readable from an input stream, false case
        template <typename T, typename = std::istream &>
        struct is_readable : std::false_type { };

        // Checks if a type is readable from an input stream, true case
        template <typename T>
        struct is_readable<T, decltype(std::declval<std::istream &>() >> std::declval<T &>())> 
            : std::true_type { };

        // Checks if all types are readable from an input stream
        template <typename... Ts>
        using all_readable = std::conjunction<is_readable<Ts>...>;


        
        // Checks if all types are parseable = derive from wrappers and are streamable
        template <typename... Ts>
        using all_parseable = std::conjunction<all_readable<Ts...>, all_wrappers<Ts...>, all_streamable<Ts...>>;



        // Implementation for a parsed nested vector, universal case
        template <bool Enable, typename...>
        struct parsed_vector_impl { };

        // Implementation for a parsed nested vector, base case
        template <typename T>
        struct parsed_vector_impl<true, T> {
            using value_type = typename T::wrapped_type;
            using type = std::vector<value_type>;
        };

        // Implementation for a parsed nested vector, recursive case
        template <typename T, typename... Ts>
        struct parsed_vector_impl<true, T, Ts...> {
            using value_type = typename parsed_vector_impl<true, Ts...>::type;
            using type = std::vector<value_type>;
        };

        // Type interface for a parsed nested vector
        template <typename... Ts>
        using parsed_vector = typename parsed_vector_impl<all_parseable<Ts...>::value, Ts...>::type;
    }

    // All file opening functions are in this namespace
    namespace {
        std::ifstream openFile(const std::string &fileName) {
            std::ifstream file { fileName };
            if (!file) {
                throw std::exception(("Failed to open file \"" + fileName + "\"").c_str());
            }
            return file;
        }

        file_ptr_stream openFilePtr(const std::string &fileName) {
            auto filePtr = std::make_unique<std::ifstream>(fileName);
            if (!filePtr->good()) {
                throw std::exception(("Failed to open file \"" + fileName + "\"").c_str());
            }
            return filePtr;
        }
    }

    // All file reading functions are in this namespace
    namespace {
        // Recursively parse stream data, base case
        template <typename In>
        parsed_vector<In> parseStream(const file_ptr_stream &in) {
            parsed_vector<In> readInput;
            std::copy(std::istream_iterator<In>(*in), std::istream_iterator<In>(), std::back_inserter(readInput));
            return readInput;
        }

        // Recursively parse stream data, recursive case
        template <typename In1, typename In2, typename... Ins>
        parsed_vector<In1, In2, Ins...> parseStream(const file_ptr_stream &in) {
            parsed_vector<In1, In2, Ins...> readInput;
            std::transform(std::istream_iterator<In1>(*in), std::istream_iterator<In1>(), std::back_inserter(readInput),
                [](const file_ptr_stream &in) {
                    return parseStream<In2, Ins...>(in);
                });
            return readInput;
        }
    }

    // All publicly-exposed functions

    // Read a single value from a file
    template <typename In>
    In readValue(const std::string &fileName) {
        auto file = openFile(fileName);
        In val;
        file >> val;
        return val;
    }

    // Read a single layer of values from a file
    template <typename In>
    parsed_vector<In> readFile(const std::string &fileName) {
        auto file = openFile(fileName);
        return parsed_vector<In>(std::istream_iterator<In>(file), std::istream_iterator<In>());
    }

    // Read multiple layers of values from a file
    template <typename In1, typename In2, typename... Ins>
    parsed_vector<In1, In2, Ins...> readFile(const std::string &fileName) {
        auto file = openFilePtr(fileName);
        return parseStream<In1, In2, Ins...>(file);
    }

    // Dump contents of file into a string
    std::string dumpFile(const std::string &fileName) {
        auto file = openFile(fileName);
        return std::string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
    }
}

void define_interface() {
    std::vector<int> input1 = in::readFile<in::value<int, ','>>("01.txt");

    std::vector<double> input2 = in::readFile<in::value<double, '\n'>>("02.txt");

    std::vector<char> input3 = in::readFile<in::value<char>>("03.txt");

    std::vector<std::string> input4 = in::readFile<in::line<std::string, '\n'>>("04.txt");

    std::vector<std::vector<int>> input5 = 
        in::readFile<in::line<std::string>, in::value<int, ','>>("05.txt");
}

int main() {
    auto start = std::chrono::system_clock::now().time_since_epoch();
    
    auto input1 = in::readFile<in::value<int, '\n'>>("04 - Big Examples/Sample Input/01.txt");
    auto input2 = in::readFile<in::value<int, ','>>("04 - Big Examples/Sample Input/02.txt");
    auto input3 = in::readFile<in::line<>, in::line<std::string, ')'>, in::value<char, 0>>("04 - Big Examples/Sample Input/03.txt");

    auto end = std::chrono::system_clock::now().time_since_epoch();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << elapsedTime.count() << " ms" << std::endl;
    return 0;
}