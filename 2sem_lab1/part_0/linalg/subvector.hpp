#ifndef SUBVECTOR_HPP
#define SUBVECTOR_HPP

#include <algorithm>
#include <cmath>
#include <initializer_list>
#include <memory>
#include <stdexcept>

template <typename T>
concept Arithmetic_plus = requires(T a, T b) {
    { a - b } -> std::same_as<T>;
    { a + b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
    { std::convertible_to<T, double> };
};

template <typename T>
class subvector {
   private:
    T* mas;
    unsigned int top;
    unsigned int capacity;

   public:
    subvector();
    explicit subvector(unsigned int count, const T& value = T());
    subvector(const subvector& other);
    subvector(subvector&& other);
    subvector& operator=(const subvector& other);
    subvector& operator=(subvector&& other);
    subvector(std::initializer_list<T> init);
    ~subvector();

    template <typename U>
    explicit subvector(const subvector<U>& other);

    void swap(subvector& other) noexcept;
    bool push_back(const T& d);
    T pop_back();
    bool resize(unsigned int new_capacity);
    void shrink_to_fit();
    void clear();
    unsigned int size() const;
    unsigned int Capacity() const;
    T& operator[](unsigned int pos) noexcept;
    const T& operator[](unsigned int pos) const noexcept;
    subvector operator-(const subvector& other) const;
    double euclidian_norm() const
    requires Arithmetic_plus<T>;
};

#include "subvector.tpp"

#endif  // SUBVECTOR_HPP