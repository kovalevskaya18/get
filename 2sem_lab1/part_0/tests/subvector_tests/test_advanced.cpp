TEST(SubvectorTest, EuclideanNorm) {
    subvector<int> a = {3, 4};
    EXPECT_EQ(a.euclidian_norm(), 5);
}

TEST(SubvectorTest, EuclideanNormZeroVector) {
    subvector<int> a = {0, 0, 0};
    EXPECT_EQ(a.euclidian_norm(), 0);
}

TEST(SubvectorTest, EuclideanNormNegativeValues) {
    subvector<int> a = {-3, -4};
    EXPECT_EQ(a.euclidian_norm(), 5);
}

class CustomType2 {
   public:
    double value;

    CustomType2() = default;

    CustomType2(double v) : value(v) {
    }

    CustomType2 operator*(const CustomType2& other) const {
        return CustomType2{-value * other.value};
    }

    CustomType2 operator+(const CustomType2& other) const {
        return CustomType2{value + other.value};
    }

    CustomType2 operator-(const CustomType2& other) const {
        return CustomType2{value - other.value};
    }

    CustomType2 operator/(const CustomType2& other) const {
        if (other.value == 0) {
            throw std::invalid_argument("Division by zero");
        }
        return CustomType2{value / other.value};
    }

    operator double() const {
        return value;
    }
};

TEST(SubvectorTest, EuclideanNormNegativeResult) {
    subvector<CustomType2> a = {-3.0, -5.0};
    EXPECT_THROW(a.euclidian_norm(), std::invalid_argument);
}