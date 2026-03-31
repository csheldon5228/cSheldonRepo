#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#include <vector>
#include <stdexcept>

template <typename T>
class ArrayStack {
private:
    std::vector<T> data;

public:
    void push(const T& value) {
        data.push_back(value);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("Stack is empty, from pop method");
        }
        if (size() == 1) {
            data.clear();
        }
        else {
            data.pop_back();
        }
    }

    T top() const {
        if (empty()) {
            throw std::out_of_range("Stack is empty, from top method");
        }
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }

    void printStack() {
        for (int i = 0; i < size(); i++) {
            printf("%s", data[i].value.c_str());
        }
        std::cout << std::endl;
    }
};

#endif
