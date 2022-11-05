//
// Created by Cheng MingBo on 2022/11/5.
//

#ifndef THREAD_SAFE_STACK_THREADSAFE_STACK_H
#define THREAD_SAFE_STACK_THREADSAFE_STACK_H
#include <mutex>
#include <exception>
#include <stack>
#include <memory>

struct empty_stack : std::exception {
    const char* what() const noexcept {
        return "this stack is empty!";
    }
};

template<typename T>
class threadsafe_stack {
private:
    std::stack<T> data;
    mutable std::mutex mutex;
public:
    threadsafe_stack() = default;
    threadsafe_stack(const threadsafe_stack& other);
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    void push(T new_value);
    std::shared_ptr<T> pop();
    void pop(T& value);
    bool empty() const;
};

template<typename T>
threadsafe_stack<T>::threadsafe_stack(const threadsafe_stack &other) {
    std::lock_guard<std::mutex> lockGuard(other.m);
    data = other.data;
}

template<typename T>
void threadsafe_stack<T>::push(T new_value) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    data.push(std::move(new_value));
    std::cout << "push: " << new_value << std::endl;
}

template<typename T>
std::shared_ptr<T> threadsafe_stack<T>::pop() {
    std::lock_guard<std::mutex> lockGuard(mutex);
    if (data.empty()) throw empty_stack();
    std::shared_ptr<T> const res {std::make_shared<T>(data.top())};
    data.pop();
    return res;
}

template<typename T>
void threadsafe_stack<T>::pop(T &value) {
    std::lock_guard<std::mutex> lockGuard(mutex);
    if (data.empty()) throw empty_stack();
    value = data.top();
    data.pop();
    std::cout << "pop: " << value << std::endl;
}

template<typename T>
bool threadsafe_stack<T>::empty() const {
    std::lock_guard<std::mutex> lockGuard(mutex);
    return data.empty();
}

#endif //THREAD_SAFE_STACK_THREADSAFE_STACK_H
