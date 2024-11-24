#include "subvector.h"

#include <initializer_list>
#include <iostream>
#include <random>
#include <cmath>
#include <stdexcept>

template <typename T>
concept Arithmetic = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
    { a - b } -> std::same_as<T>;
    { a * b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;

};


template <typename T>
class Matrix {
   private:
    subvector<T> data_;  // какой-то класс вектора: subvector или std::vector
    // предполагается, что хранение будет происходить в одном линейном массиве,
    // а не как с двойным указателем
    // предполагается, что матрица хранится построчно (Row-Major Ordering)
    unsigned int cols_{};
    unsigned int rows_{};

   public:
    Matrix() = default;//ctor default

    Matrix(const Matrix& other) = default;//copy ctor

    Matrix(Matrix&& other) = default;//move ctor

    Matrix& operator=(const Matrix& other) = default;//assign operator

    Matrix& operator=(Matrix&& other) = default;//move assign operator

    ~Matrix() = default;//dtor

    template <typename U>
    explicit Matrix(const Matrix<U>& other) {


        rows_ = other.rows();
        cols_ = other.cols();
        data_ = subvector<T>(rows_ * cols_);
        for (unsigned int i = 0; i < rows_; ++i) {
            for (unsigned int j = 0; j < cols_; ++j) {
                (*this)(i, j) = static_cast<T>(other(i, j));
            }
        }
    }//copy ctor with cast

    Matrix(std::initializer_list<std::initializer_list<T>> init) : cols_(0), rows_(init.size()) {//init is two-dimensional array
        if (init.size() != 0) {
            cols_ = init.begin()->size();//size of the 1st row(amount of columns)
            data_ = subvector<T>(rows_ * cols_);
            unsigned int index = 0;
            for (const auto& row : init) {
                for (const auto& elem : row) {
                    data_[index] = elem;
                    index++;
                }
            }
        }
    }//convenient ctor(to do like this:Matrix<int> m{{1, 0, 2, -1}, {3, 0, 0, 5}, {2, 1, 4, -3}, {1, 0, 5, 0}}

    Matrix(unsigned rows, unsigned cols, T value = T()) : cols_(cols), rows_(rows) {
        data_ = subvector<T>(rows_ * cols_, value);
    }

    static Matrix<int> Identity(unsigned rows, unsigned cols) {
        Matrix<int> result(rows, cols);
        for (unsigned i = 0; i < std::min(rows, cols); i++) {
            result(i, i) = 1;
        }
        return result;
    }
    //для получения матрицы с заданным детерминантом построим матрицу с ненулевыми элементами
    //на главной диагонали, и нулевыми вне диагонали. Затем поменяем местами строки и столбцы матрицы
    //но так, чтобы детерминант не поменялся
    static Matrix getSpecificDeterminant(unsigned int n, T determinant) {
        Matrix result(n, n);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution dis(1.0, 10.0);

        T product = 1;
        for (unsigned int i = 0; i < n - 1; ++i) {
            result(i, i) = static_cast<T>(dis(gen));
            product *= result(i, i);
        }
        result(n - 1, n - 1) = determinant / product;
        result.shuffle(gen);
        return result;
    }

    // для целочисленных детерминантов
    static Matrix getSpecificDeterminant(unsigned int n, T determinant) requires std::integral<T> {
        // проверка requires std::integral<T> нужна для того, чтобы компилятор понимал, когда мы вызываем этот метод для целочисленного типа
        // то надо вызывать именно этот метод, а не предыдущий. Без проверки код не скомпилируется
        T determinant_copy = std::abs(determinant);
        subvector<T> factors;


        while (determinant_copy % 2 == 0) {
            factors.push_back(2);
            determinant_copy /= 2;
        }
        for (T i = 3; i <= std::sqrt(determinant_copy); i += 2) {//на кратность 2 проверили - идём через 2
            //у determinant_copy нет делителей, больших корня квадратного из него
            while (determinant_copy % i == 0) {
                factors.push_back(i);
                determinant_copy /= i;
            }
        }
        if (determinant_copy > 2) {
            factors.push_back(determinant_copy);
        }
        Matrix<T> result(n, n);

        T product = 1;
        for (unsigned int i = 0; i < n - 1; ++i) {

            T value = (i < factors.size()) ? factors[i] : 1;
            result(i, i) = value;
            product *= value;
        }

        result(n - 1, n - 1) = determinant / product;
        std::random_device rd;
        std::mt19937 gen(rd());
        result.shuffle(gen);
        return result;
    }

    // getters
    unsigned int rows() const {
        return rows_;
    }

    unsigned int cols() const {
        return cols_;
    }
    //транспонирую себя
    Matrix& transpose() {
        Matrix transposed = Matrix(cols_, rows_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < cols_; ++j) {
                transposed(j, i) = (*this)(i, j);
            }
        }
        *this = transposed;
        return *this;
    }
    //копирую себя, транспонирую и возвращаю

    Matrix transpose() const {
        Matrix transposed = Matrix(cols_, rows_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < cols_; ++j) {
                transposed(j, i) = (*this)(i, j);
            }
        }
        return transposed;
    }
    //возвращает ссылку на элемент, тогда его можно изменить
    T& operator()(unsigned int row, unsigned int col) {
        try {
            return data_[row * cols_ + col];
        } catch (const std::out_of_range& e) {
            std::cerr << "Out of range error in matrix element access: " << e.what() << std::endl;
            throw;
        }
    }
    //копирует нужный элемент, потом возвращает(копия не привязана к элементу матрицы)
    T operator()(unsigned int row, unsigned int col) const {
        try {
            return data_[row * cols_ + col];
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Out of range error in matrix element access: " << e.what() << std::endl;
            throw;
        }
    }

    // Дополнительно

    void shuffle(std::mt19937& gen) {
        // генерируем последовательности перестановок для строк и столбцов. Для каждого их должно
        // быть четное количество, чтобы не поменять определитель
        if (rows_ == 0 || cols_ == 0) {
            return;
        }

        subvector<unsigned int> row_perm(rows_);
        for (unsigned int i = 0; i < rows_; ++i) {
            row_perm[i] = i;
        }

        unsigned int row_swaps = 0;
        for (unsigned int i = 0; i < rows_; ++i) {
            unsigned int j = std::uniform_int_distribution<unsigned int>(i, rows_ - 1)(gen);
            if (i != j) {
                std::swap(row_perm[i], row_perm[j]);
                row_swaps++;
            }
        }

        if (row_swaps % 2 == 1 && rows_ > 1) {
            unsigned int i = 0;
            unsigned int j = 1;
            std::swap(row_perm[i], row_perm[j]);
        }

        subvector<unsigned int> col_perm(cols_);
        for (unsigned int i = 0; i < cols_; ++i) {
            col_perm[i] = i;
        }

        unsigned int col_swaps = 0;
        for (unsigned int i = 0; i < cols_; ++i) {
            unsigned int j = std::uniform_int_distribution<unsigned int>(i, cols_ - 1)(gen);
            if (i != j) {
                std::swap(col_perm[i], col_perm[j]);
                col_swaps++;
            }
        }

        if (col_swaps % 2 == 1 && cols_ > 1) {
            unsigned int i = 0;
            unsigned int j = 1;
            std::swap(col_perm[i], col_perm[j]);
        }
        //создаём матрицу в которую копируем нашу матрицу

        Matrix temp(*this);

        for (unsigned int i = 0; i < rows_; ++i) {
            for (unsigned int j = 0; j < cols_; ++j) {
                (*this)(i, j) = temp(row_perm[i], col_perm[j]);//меняем местами строки и столбцы в нашей матрице
                                                               //через созданную матрицу temp
            }
        }
    }
    //создание подматрицы
    Matrix submatrix(
        unsigned int row_begin, unsigned int col_begin, unsigned int row_end,
        unsigned int col_end) const {
        if (row_begin >= rows_ || row_end > rows_ || col_begin >= cols_ || col_end > cols_ ||
            row_begin >= row_end || col_begin >= col_end) {
            throw std::out_of_range("Submatrix indices are out of range");
        }
        unsigned int subRows = row_end - row_begin;
        unsigned int subCols = col_end - col_begin;
        Matrix submatrix(subRows, subCols);

        for (unsigned int i = 0; i < subRows; ++i) {
            for (unsigned int j = 0; j < subCols; ++j) {
                submatrix(i, j) = (*this)(row_begin + i, col_begin + j);
            }
        }
        return submatrix;
    }
    //получаем подматрицу без 1 строки и 1  столбца - нужно для вычисления детерминанта
    Matrix eliminate_row_col(unsigned int elim_row, unsigned int elim_col) {
        Matrix submatrix(rows_ - 1, cols_ - 1);
        int subRow = 0;

        for (int row = 0; row < rows_; row++) {
            if (row == elim_row) {
                continue;
            }
            int subCol = 0;
            for (int col = 0; col < cols_; col++) {
                if (col == elim_col) {
                    continue;
                }
                submatrix(subRow, subCol) = (*this)(row, col);
                subCol++;
            }
            subRow++;
        }
        return submatrix;
    }

    //матричное умножение
    Matrix operator*(const Matrix& other)
    requires Arithmetic<T>
    {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Matrix dimensions must be compatible");
        }
        Matrix result(rows_, other.cols_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < other.cols_; ++j) {
                for (unsigned k = 0; k < cols_; ++k) {
                    result(i, j) = result(i, j) + (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }
    //умножение матрицы на вектор
    subvector<T> operator*(const subvector<T>& other) const
    requires Arithmetic<T>
    {
        if (cols_ != other.size()) {
            throw std::invalid_argument("Matrix and vector dimensions must be compatible");
        }
        subvector<T> result(rows_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < cols_; ++j) {
                result[i] = result[i] + (*this)(i, j) * other[j];
            }
        }
        return result;
    }
    //умножение матрицы на константу

    Matrix operator*(const T& value)
    requires Arithmetic<T>
    {
        Matrix result(rows_, cols_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < cols_; ++j) {
                result(i, j) = (*this)(i, j) * value;
            }
        }
        return result;
    }
    //сложение матриц
    Matrix operator+(const Matrix& other)
    requires Arithmetic<T>
    {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrix dimensions must be compatible");
        }
        Matrix result(rows_, cols_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < cols_; ++j) {
                result(i, j) = (*this)(i, j) + other(i, j);
            }
        }
        return result;
    }
    //вычитание матриц
    Matrix operator-(const Matrix& other)
    requires Arithmetic<T>
    {
        if (rows_ != other.rows_ || cols_ != other.cols_) {
            throw std::invalid_argument("Matrix dimensions must be compatible");
        }
        Matrix result(rows_, cols_);
        for (unsigned i = 0; i < rows_; ++i) {
            for (unsigned j = 0; j < cols_; ++j) {
                result(i, j) = (*this)(i, j) - other(i, j);
            }
        }
        return result;
    }

    // 5) Любые методы, которые вам будут удобны для работы с матрицей
    // например, созданием подматрицы, перестановка строк (столбцов), умонжение
    // строки (столбца) на число и так далее
};
//вычисление детерминанта
//функция ниже более быстрая, приводит матрицу к верхнетреугольному виду и считает произведение элементов на главной диагонали. Чтобы не переусложнять решено сделать ее только для тех типов, которые приводятся к double.
template <typename T>
double determinant(const Matrix<T>& matrix_in)
requires std::convertible_to<T, double>
{
    Matrix<double> matrix(matrix_in);
    if (matrix.rows() != matrix.cols()) {
        throw std::invalid_argument("Matrix must be square");
    }
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

        for (int k = i + 1; k < n; ++k) {
            double factor = matrix(k, i) / matrix(i, i);



            for (int j = i; j < n; ++j) {
                matrix(k, j) = matrix(k, j) - matrix(i, j) * factor;
            }
        }
    }
    double det = sign;
    for (int i = 0; i < n; ++i) {
        det = det * matrix(i, i);
    }
    return det;
}

template <typename T>
subvector<double> solve_system(Matrix<T> matrix_in, subvector<T> results_in)
requires std::convertible_to<T, double>
{
    Matrix<double> matrix(matrix_in);
    subvector<double> results(results_in);
    unsigned int n = matrix.rows();
    double det = determinant(matrix);
    if (std::abs(det) < 1e-5) {
        throw std::invalid_argument("Matrix must not be singular");
    }
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
        
        std::swap(results[maxRow], results[i]);

        for (int k = i + 1; k < n; ++k) {
            double factor = matrix(k, i) / matrix(i, i);
            for (int j = i; j < n; ++j) {
                matrix(k, j) -= matrix(i, j) * factor;
            }
            results[k] -= results[i] * factor;
        }
    }

    subvector<double> solution(n);
    for (int i = n - 1; i >= 0; --i) {
        solution[i] = results[i];
        for (int j = i + 1; j < n; ++j) {
            solution[i] -= matrix(i, j) * solution[j];
        }
        solution[i] /= matrix(i, i);
    }

    return solution;
}


inline bool check_solution(
    const Matrix<double>& matrix, const subvector<double>& results,
    const subvector<double>& solution) {
    subvector<double> check;
    try {
        check = matrix * solution - results;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid arguments for vector substraction: " << e.what() << std::endl;
        throw;
    }
    try {
        return check.euclidian_norm() < 1e-5;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid argument for euclidian norm: " << e.what() << std::endl;
        throw;
    }
}
