#pragma once

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <memory>
#include <stdexcept>

template <typename T>
subvector<T>::subvector() : mas(nullptr), top(0), capacity(0) {
}  // ctor default

template <typename T>
subvector<T>::subvector(unsigned int count, const T& value)
    : mas(new T[count]), top(count), capacity(count) {
    for (unsigned int i = 0; i < count; i++) {
        mas[i] = value;
    }
}  // direct ctor

// explicit для предотвращения неявного приведения типов

template <typename T>
subvector<T>::subvector(const subvector& other) : subvector() {
    for (unsigned int i = 0; i < other.size(); i++) {
        push_back(other[i]);
    }
}  // copy ctor

template <typename T>
subvector<T>::subvector(subvector&& other) : subvector() {
    swap(other);
}  // move ctor

template <typename T>
subvector<T>& subvector<T>::operator=(const subvector& other) {
    if (this == &other) {
        return *this;
    }
    clear();

    for (unsigned int i = 0; i < other.size(); i++) {
        push_back(other[i]);
    }
    return *this;
}  // assign operator

template <typename T>
subvector<T>& subvector<T>::operator=(subvector&& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    swap(other);
    return *this;
}  // move assign ctor

template <typename T>
subvector<T>::subvector(std::initializer_list<T> init) : top(0), capacity(init.size()) {
    mas = new T[capacity];

    for (const auto& x : init) {
        push_back(x);
    }
}  // convinient ctor (to do like this: subvector<int> x = {1, 2, 3})

template <typename T>
subvector<T>::~subvector() {
    delete[] mas;
    mas = nullptr;
    top = 0;
    capacity = 0;
}  // dtor

template <typename T>
template <typename U>
subvector<T>::subvector(const subvector<U>& other) {
    top = other.size();
    capacity = other.Capacity();

    mas = new T[capacity];
    for (unsigned int i = 0; i < top; ++i) {
        mas[i] = static_cast<T>(other[i]);
    }
}  // convinient copy ctor with type cast

template <typename T>
void subvector<T>::swap(subvector& other) noexcept {
    std::swap(mas, other.mas);
    std::swap(top, other.top);
    std::swap(capacity, other.capacity);
}

template <typename T>
bool subvector<T>::push_back(const T& d) {
    if (top == capacity) {
        resize(capacity == 0 ? 1 : 2 * capacity);
    }
    mas[top] = d;
    top++;
    return true;
}

template <typename T>
T subvector<T>::pop_back() {
    if (top > 0) {
        top--;
        return *std::next(mas, top);
    }
    return T();
}

template <typename T>
bool subvector<T>::resize(unsigned int new_capacity) {
    T* new_data = new T[new_capacity];
    for (unsigned int i = 0; i < std::min(top, new_capacity); i++) {
        new_data[i] = mas[i];
    }
    delete[] mas;
    mas = new_data;
    capacity = new_capacity;
    top = std::min(top, capacity);
    return true;
}

template <typename T>
void subvector<T>::shrink_to_fit() {
    resize(top);
}

template <typename T>
void subvector<T>::clear() {
    top = 0;
}

template <typename T>
unsigned int subvector<T>::size() const {
    return top;
}

template <typename T>
unsigned int subvector<T>::Capacity() const {
    return capacity;
}

template <typename T>
T& subvector<T>::operator[](unsigned int pos) noexcept {
    return mas[pos];
}

template <typename T>
const T& subvector<T>::operator[](unsigned int pos) const noexcept {
    return mas[pos];
}

template <typename T>
subvector<T> subvector<T>::operator-(const subvector& other) const {
    if (top != other.size()) {
        throw std::invalid_argument("Vectors must have the same size");
    }
    subvector result(top);
    for (unsigned int i = 0; i < top; i++) {
        result[i] = (*this)[i] - other[i];
    }
    return result;
}

template <typename T>
double subvector<T>::euclidian_norm() const
requires Arithmetic_plus<T>
{
    T result = 0;
    for (unsigned int i = 0; i < top; i++) {
        result = result + (*this)[i] * (*this)[i];
    }
    if (static_cast<double>(result) < 0) {
        throw std::invalid_argument("Negative value in sqrt");
    }
    return std::sqrt(static_cast<double>(result));
}
