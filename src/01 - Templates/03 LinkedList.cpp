// Template class example, and smart memory management

#include <iostream>
#include <memory>

// Very basic linked list example
template <typename T>
class linked_list {
private:
    struct node {
        T data;
        std::unique_ptr<node> next;

        node(const T &data) : data(data), next(nullptr) { }
    };

    std::unique_ptr<node> head;

public:
    linked_list() : head(nullptr) { }

    void push(const T &val) {
        node *prev = nullptr;
        node *it = head.get();
        while (it) {
            prev = it;
            it = it->next.get();
        }
        if (!prev) {
            head = std::make_unique<node>(val);
        }
        else {
            prev->next = std::make_unique<node>(val);
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const linked_list &list) {
        node *it = list.head.get();
        while (it) {
            out << it->data << " => ";
            it = it->next.get();
        }
        return out;
    }
};

int run_list() {
    linked_list<int> intList;
    intList.push(1);
    intList.push(2);
    intList.push(3);
    std::cout << intList << std::endl;

    linked_list<std::string> strList;
    strList.push("This");
    strList.push("is");
    strList.push("fun!");
    std::cout << strList << std::endl;

    return 0;
}