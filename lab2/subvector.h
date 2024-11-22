#include <algorithm>
#include <initializer_list>
#include <memory>

// template restriction
template <typename T>
concept Arithmetic_plus = requires(T a, T b) {
    { a - b } -> std::same_as<T>;
    { a + b } -> std::same_as<T>;
    { a* b } -> std::same_as<T>;
    { a / b } -> std::same_as<T>;
    { std::convertible_to<T, double> };

};  // поискав на cppreference можно понять что последнее это достаточное условие для
    // std::sqrt(). Чтобы это условие выполлнялось нужно чтобы у класса был
    // определен оператор конверсии в double


template <typename T>
class subvector {
   private:
    T* mas_;
    unsigned int size_;
    unsigned int capacity_;

   public:
    subvector() : mas_(nullptr), size_(0), capacity_(0) {
    }//ctor default

    explicit subvector(unsigned int count, const T& value = T())
        : mas_(new T[count]), size_(count), capacity_(count) {
        for (unsigned int i = 0; i < count; i++) {
            mas_[i] = value;
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

    subvector(std::initializer_list<T> init) : size_(0), capacity_(init.size()) {
        mas_ = new T[capacity_];

        for (const auto& x : init) {
            push_back(x);
        }
    }//convinient ctor (to do like this: subvector<int> x = {1, 2, 3})

    ~subvector() {
        delete[] mas_;
        mas_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }//dtor





    template <typename U>
    explicit subvector(const subvector<U>& other) {
        size_ = other.size();
        capacity_ = other.capacity();


        mas_ = new T[capacity_];
        for (unsigned int i = 0; i < size_; ++i) {
            mas_[i] = static_cast<T>(other[i]);
        }
    }//convinient copy ctor with type cast




    void swap(subvector& other) noexcept {
        std::swap(mas_, other.mas_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    bool push_back(const T& d) {
        if (size_ == capacity_) {
            resize(capacity_ == 0 ? 1 : 2 * capacity_);
        }
        mas_[size_]= d;
        size_++;
        return true;
    }

    T pop_back() {
        if (size_ > 0) {
            size_--;
            return *std::next(mas_, size_);
        }
        return T();
    }

    bool resize(unsigned int new_capacity) {
        T* new_data = new T[new_capacity];
        for (unsigned int i = 0; i < std::min(size_, new_capacity); i++) {
            new_data[i] = mas_[i];
        }
        delete[] mas_;
        mas_ = new_data;
        capacity_ = new_capacity;
        size_ = std::min(size_, capacity_);
        return true;
    }




    void shrink_to_fit() {
        resize(size_);
    }

    void clear() {
        size_ = 0;
    }

    unsigned int size() const {
        return size_;
    }

    unsigned int capacity() const {
        return capacity_;
    }



    T& operator[](unsigned int pos) {
        if (pos >= size_) {
            throw std::out_of_range("Index out of range");
        }

        return mas_[pos];
    }




    const T& operator[](unsigned int pos) const {
        if (pos >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return mas_[pos];
    }

    subvector operator-(const subvector& other) const {
        if (size_ != other.size()) {
            throw std::invalid_argument("Vectors must have the same size");
        }
        subvector result(size_);
        for (unsigned int i = 0; i < size_; i++) {
            result[i] = (*this)[i] - other[i];
        }
        return result;
    }

    double euclidian_norm() const
    requires Arithmetic_plus<T>
    {
        T result = 0;
        for (unsigned int i = 0; i < size_; i++) {
            result = result + (*this)[i] * (*this)[i];
        }
        if (static_cast<double>(result) < 0) {
            throw std::invalid_argument("Negative value in sqrt");
        }
        return std::sqrt(static_cast<double>(result));
    }
};
