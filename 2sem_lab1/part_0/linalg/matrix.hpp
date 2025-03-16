#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "subvector.hpp"

#include <cmath>
#include <initializer_list>
#include <iostream>
#include <random>
#include <stdexcept>

template <typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { a* b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
};

template <typename T>
class Matrix {
   private:
    subvector<T> data_;
    unsigned int cols_{};
    unsigned int rows_{};

   public:
    Matrix() = default;
    Matrix(const Matrix& other) = default;
    Matrix(Matrix&& other) = default;
    Matrix& operator=(const Matrix& other) = default;
    Matrix& operator=(Matrix&& other) = default;
    ~Matrix() = default;

    template <typename U>
    explicit Matrix(const Matrix<U>& other);

    Matrix(std::initializer_list<std::initializer_list<T>> init);
    Matrix(unsigned rows, unsigned cols, T value = T());

    static Matrix<int> Identity(unsigned rows, unsigned cols);
    static Matrix getSpecificDeterminant(unsigned int n, T determinant);

    static Matrix getSpecificDeterminant(unsigned int n, T determinant)
    requires std::integral<T>;

    unsigned int rows() const;
    unsigned int cols() const;
    Matrix& transpose();
    Matrix transpose() const;
    T& operator()(unsigned int row, unsigned int col);
    T operator()(unsigned int row, unsigned int col) const;
    void shuffle(std::mt19937& gen);
    Matrix submatrix(
        unsigned int row_begin, unsigned int col_begin, unsigned int row_end,
        unsigned int col_end) const;
    Matrix eliminate_row_col(unsigned int elim_row, unsigned int elim_col);
};

template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs)
requires Arithmetic<T>;

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const Matrix<T>& rhs)
requires Arithmetic<T>;

template <typename T>
subvector<T> operator*(const Matrix<T>& lhs, const subvector<T>& rhs)
requires Arithmetic<T>;

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs)
requires Arithmetic<T>;

template <typename T>
Matrix<T> operator*(const Matrix<T>& lhs, const T& value)
requires Arithmetic<T>;

template <typename T>
Matrix<T> operator*(const T& value, const Matrix<T>& rhs)
requires Arithmetic<T>;

template <typename T>
double determinant(const Matrix<T>& matrix_in)
requires std::convertible_to<T, double>;

template <typename T>
subvector<double> solve_system(Matrix<T> matrix_in, subvector<T> results_in)
requires std::convertible_to<T, double>;

bool check_solution(
    const Matrix<double>& matrix, const subvector<double>& results,
    const subvector<double>& solution);

double forward_elimination(Matrix<double>& matrix, subvector<double>& results);

#include "matrix.tpp"

#endif  // MATRIX_HPP
