TEST(MatrixTest, AssignmentOperator) {
    Matrix<int> m1{{1, 2}, {3, 4}};
    Matrix<int> m2;
    m2 = m1;
    EXPECT_EQ(m2.rows(), 2);
    EXPECT_EQ(m2.cols(), 2);
    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
    EXPECT_EQ(m2(1, 0), 3);
    EXPECT_EQ(m2(1, 1), 4);
}

TEST(MatrixTest, MoveAssignmentOperator) {
    Matrix<int> m1{{1, 2}, {3, 4}};
    Matrix<int> m2;
    m2 = std::move(m1);
    EXPECT_EQ(m2.rows(), 2);
    EXPECT_EQ(m2.cols(), 2);
    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
    EXPECT_EQ(m2(1, 0), 3);
    EXPECT_EQ(m2(1, 1), 4);
}

TEST(MatrixTest, AdditionOperator) {
    Matrix<int> m1{{1, 2}, {3, 4}};
    Matrix<int> m2{{5, 6}, {7, 8}};
    Matrix<int> result = m1 + m2;
    EXPECT_EQ(result(0, 0), 6);
    EXPECT_EQ(result(0, 1), 8);
    EXPECT_EQ(result(1, 0), 10);
    EXPECT_EQ(result(1, 1), 12);
}

TEST(MatrixTest, SubtractionOperator) {
    Matrix<int> m1{{5, 6}, {7, 8}};
    Matrix<int> m2{{1, 2}, {3, 4}};
    Matrix<int> result = m1 - m2;
    EXPECT_EQ(result(0, 0), 4);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 4);
    EXPECT_EQ(result(1, 1), 4);
}

TEST(MatrixTest, ScalarMultiplicationOperator) {
    Matrix<int> m{{1, 2}, {3, 4}};
    Matrix<int> result = m * 2;
    Matrix<int> result_1 = 2 * m;
    EXPECT_EQ(result(0, 0), 2);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 6);
    EXPECT_EQ(result(1, 1), 8);

    EXPECT_EQ(result_1(0, 0), 2);
    EXPECT_EQ(result_1(0, 1), 4);
    EXPECT_EQ(result_1(1, 0), 6);
    EXPECT_EQ(result_1(1, 1), 8);
}

TEST(MatrixTest, MatrixVectorMultiplicationInvalidDimensions) {
    Matrix<int> m{{1, 2}, {3, 4}};
    subvector<int> v{1, 2, 3};
    EXPECT_THROW(m * v, std::invalid_argument);
}

TEST(MatrixTest, MatrixVectorMultiplicationOperator) {
    Matrix<int> m1{{1, 2, 3}, {4, 5, 6}};
    Matrix<int> m2{{7, 8}, {9, 10}, {11, 12}};
    Matrix<int> result = m1 * m2;
    EXPECT_EQ(result.rows(), 2);
    EXPECT_EQ(result.cols(), 2);
    EXPECT_EQ(result(0, 0), 58);
    EXPECT_EQ(result(0, 1), 64);
    EXPECT_EQ(result(1, 0), 139);
    EXPECT_EQ(result(1, 1), 154);
}

struct CustomType {
    int value;

    CustomType(int v = 0) : value(v) {
    }

    CustomType operator+(const CustomType& other) const {
        return CustomType(value + other.value);
    }

    CustomType operator-(const CustomType& other) const {
        return CustomType(value - other.value);
    }

    CustomType operator*(const CustomType& other) const {
        return CustomType(value * other.value);
    }

    CustomType operator/(const CustomType& other) const {
        return CustomType(value / other.value);
    }

    bool operator==(const CustomType& other) const {
        return value == other.value;
    }
};

TEST(MatrixTest, CustomType) {
    Matrix<CustomType> m1{{CustomType(1), CustomType(2)}, {CustomType(3), CustomType(4)}};
    Matrix<CustomType> m2{{CustomType(5), CustomType(6)}, {CustomType(7), CustomType(8)}};
    Matrix<CustomType> result = m1 + m2;
    EXPECT_EQ(result(0, 0), CustomType(6));
    EXPECT_EQ(result(0, 1), CustomType(8));
    EXPECT_EQ(result(1, 0), CustomType(10));
    EXPECT_EQ(result(1, 1), CustomType(12));
}
