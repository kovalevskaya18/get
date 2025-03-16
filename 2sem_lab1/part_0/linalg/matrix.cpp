#include "matrix.hpp"

#define INSTANTIATE_MATRIX_FOR_TYPE(T)                                \
    template class Matrix<T>;                                         \
    template Matrix<T> operator+(const Matrix<T>&, const Matrix<T>&); \
    template Matrix<T> operator*(const Matrix<T>&, const Matrix<T>&); \
    template subvector<T> operator*(const Matrix<T>& lhs, const subvector<T>& rhs); \
    template Matrix<T> operator-(const Matrix<T>&, const Matrix<T>&); \
    template Matrix<T> operator*(const Matrix<T>&, const T&);         \
    template Matrix<T> operator*(const T&, const Matrix<T>&);         \
    template double determinant(const Matrix<T>& matrix_in);          \
    template subvector<double> solve_system(Matrix<T> matrix_in, subvector<T> results_in);

INSTANTIATE_MATRIX_FOR_TYPE(int)
INSTANTIATE_MATRIX_FOR_TYPE(double)
INSTANTIATE_MATRIX_FOR_TYPE(float)

bool check_solution(
    const Matrix<double>& matrix, const subvector<double>& results,
    const subvector<double>& solution) {
    subvector<double> check;
    try {
        check = matrix * solution - results;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid arguments for vector substraction: " << e.what() << std::endl;
        throw;
    }
    try {
        return check.euclidian_norm() < 1e-5;
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument for euclidian norm: " << e.what() << std::endl;
        throw;
    }
}

double forward_elimination(Matrix<double>& matrix, subvector<double>& results) {
    unsigned int n = matrix.rows();
    double sign = 1;
    for (int i = 0; i < n; ++i) {
        double maxEl = matrix(i, i);
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (matrix(k, i) > maxEl) {
                maxEl = matrix(k, i);
                maxRow = k;
            }
        }
        for (int j = 0; j < n; ++j) {
            std::swap(matrix(maxRow, j), matrix(i, j));
        }
        if (maxRow != i) {
            sign = -sign;
        }
        if (results.size() != 0) {
            std::swap(results[maxRow], results[i]);
        }
        for (int k = i + 1; k < n; ++k) {
            double factor = matrix(k, i) / matrix(i, i);
            for (int j = i; j < n; ++j) {
                matrix(k, j) -= matrix(i, j) * factor;
            }
            if (results.size() != 0) {
                results[k] -= results[i] * factor;
            }
        }
    }
    return sign;
}