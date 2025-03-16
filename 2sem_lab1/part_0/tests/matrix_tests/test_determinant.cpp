TEST(MatrixTest, DeterminantNonSquareMatrix) {
    const Matrix<int> m{{1, 2, 3}, {4, 5, 6}};
    EXPECT_THROW(determinant(m), std::invalid_argument);
}

TEST(MatrixTest, Determinant2x2) {
    const Matrix<int> m{{1, 2}, {-3, 4}};
    EXPECT_EQ(determinant(m), 10);
}

TEST(MatrixTest, Determinant3x3) {
    const Matrix<int> m{{6, 1, 1}, {4, -2, 5}, {2, 8, 7}};
    EXPECT_EQ(determinant(m), -306);
}

TEST(MatrixTest, SpecificDeterminant5x5) {
    const int determinant_target = 120;
    const Matrix<int> matrix = Matrix<int>::getSpecificDeterminant(5, determinant_target);
    EXPECT_EQ(determinant(matrix), determinant_target);
}

TEST(MatrixTest, SpecificDeterminant50x50) {
    const int expectedDeterminant = 123'456;
    const Matrix<int> m = Matrix<int>::getSpecificDeterminant(50, expectedDeterminant);
    EXPECT_EQ(determinant(m), expectedDeterminant);
}

TEST(MatrixTest, SpecificDeterminant200x200) {
    const int expected_determinant = 1'234'567'890;
    const Matrix<int> m = Matrix<int>::getSpecificDeterminant(200, expected_determinant);
    EXPECT_EQ(determinant(m), expected_determinant);
}

TEST(MatrixTest, SpecificDeterminantDouble) {
    const Matrix<double> matrix = Matrix<double>::getSpecificDeterminant(3, 10.0);
    const double det = determinant(matrix);
    EXPECT_NEAR(det, 10.0, 1e-5);

    const Matrix<double> matrix2 = Matrix<double>::getSpecificDeterminant(4, 20.0);
    const double det2 = determinant(matrix2);
    EXPECT_NEAR(det2, 20.0, 1e-5);
}
