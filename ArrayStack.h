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
        // TODO
        data.push_back(value);
    }

    void pop() {
        // TODO
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        if (size() == 1) {
            data.clear();
        }
        else {
            data.pop_back();
        }
    }

    T top() const {
        // TODO
        if (empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return data.back();
    }

    bool empty() const {
        // TODO
        return data.empty();
    }

    int size() const {
        // TODO
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
