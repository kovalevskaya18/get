TEST(MatrixTest, DefaultConstructor) {
    Matrix<int> m;
    EXPECT_EQ(m.rows(), 0);
    EXPECT_EQ(m.cols(), 0);
}

TEST(MatrixTest, InitializerListConstructor) {
    Matrix<int> m{{1, 2}, {3, 4}};
    EXPECT_EQ(m.rows(), 2);
    EXPECT_EQ(m.cols(), 2);
    EXPECT_EQ(m(0, 0), 1);
    EXPECT_EQ(m(0, 1), 2);
    EXPECT_EQ(m(1, 0), 3);
    EXPECT_EQ(m(1, 1), 4);
}

TEST(MatrixTest, CopyConstructor) {
    Matrix<int> m1{{1, 2}, {3, 4}};
    Matrix<int> m2 = m1;
    EXPECT_EQ(m2.rows(), 2);
    EXPECT_EQ(m2.cols(), 2);
    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
    EXPECT_EQ(m2(1, 0), 3);
    EXPECT_EQ(m2(1, 1), 4);
}

TEST(MatrixTest, MoveConstructor) {
    Matrix<int> m1{{1, 2}, {3, 4}};
    Matrix<int> m2 = std::move(m1);
    EXPECT_EQ(m2.rows(), 2);
    EXPECT_EQ(m2.cols(), 2);
    EXPECT_EQ(m2(0, 0), 1);
    EXPECT_EQ(m2(0, 1), 2);
    EXPECT_EQ(m2(1, 0), 3);
    EXPECT_EQ(m2(1, 1), 4);
}