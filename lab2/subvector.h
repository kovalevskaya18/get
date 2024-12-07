
#include <algorithm>
#include <initializer_list>
#include <memory>
#include <cmath>
#include <stdexcept>

// template restriction
template <typename T>
concept Arithmetic_plus = requires(T a, T b) {
    { a - b } -> std::same_as<T>;
    { a + b } -> std::same_as<T>;
    { a* b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
    { std::convertible_to<T, double> };

};  // поискав на cppreference можно понять что последнее это достаточное условие для
// std::sqrt(). Чтобы это условие выполнялось нужно чтобы у класса был
// определен оператор конверсии в double


template <typename T>
class subvector {
public: // for profilers, but this part must be private
    T* mas;
    unsigned int top;
    unsigned int capacity;


public:

    subvector() : mas(nullptr), top(0), capacity(0) {
    }//ctor default

    explicit subvector(unsigned int count, const T& value = T())
        : mas(new T[count]), top(count), capacity(count) {
        for (unsigned int i = 0; i < count; i++) {
            mas[i] = value;
        }
    }//direct ctor
    //explicit для предотвращения неявного приведения типов

    subvector(const subvector& other) : subvector() {

        for (unsigned int i = 0; i < other.size(); i++) {
            push_back(other[i]);
        }
    }//copy ctor

    subvector(subvector&& other) : subvector() {
        swap(other);
    }//move ctor

    subvector& operator=(const subvector& other) {
        if (this == &other) {
            return *this;
        }
        clear();



        for (unsigned int i = 0; i < other.size(); i++) {
            push_back(other[i]);
        }
        return *this;
    }//assign operator

    subvector& operator=(subvector&& other) {


        if (this == &other) {
            return *this;
        }
        clear();
        swap(other);
        return *this;
    }//move assign ctor

    subvector(std::initializer_list<T> init) : top(0), capacity(init.size()) {
        mas = new T[capacity];

        for (const auto& x : init) {
            push_back(x);
        }
    }//convinient ctor (to do like this: subvector<int> x = {1, 2, 3})

    ~subvector() {
        delete[] mas;
        mas = nullptr;
        top = 0;
        capacity = 0;
    }//dtor





    template <typename U>
    explicit subvector(const subvector<U>& other) {
        top = other.size();
        capacity = other.capacity();


        mas = new T[capacity];
        for (unsigned int i = 0; i < top; ++i) {
            mas[i] = static_cast<T>(other[i]);
        }
    }//convinient copy ctor with type cast




    void swap(subvector& other) noexcept {
        std::swap(mas, other.mas);
        std::swap(top, other.top);
        std::swap(capacity, other.capacity);
    }

    bool push_back(const T& d) {
        if (top == capacity) {
            resize(capacity == 0 ? 1 : 2 * capacity);
        }
        mas[top] = d;
        top++;
        return true;
    }

    T pop_back() {
        if (top > 0) {
            top--;
            return *std::next(mas, top);
        }
        return T();
    }

    bool resize(unsigned int new_capacity) {
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




    void shrink_to_fit() {
        resize(top);
    }

    void clear() {
        top = 0;
    }

    unsigned int size() const {
        return top;
    }

    unsigned int Capacity() const {
        return capacity;
    }




    T& operator[](unsigned int pos) noexcept{


        return mas[pos];
    }




    const T& operator[](unsigned int pos) const noexcept{

        return mas[pos];
    }

    subvector operator-(const subvector& other) const {
        if (top != other.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        subvector result(top);
        for (unsigned int i = 0; i < top; i++) {
            result[i] = (*this)[i] - other[i];
        }
        return result;
    }

    double euclidian_norm() const
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
};
