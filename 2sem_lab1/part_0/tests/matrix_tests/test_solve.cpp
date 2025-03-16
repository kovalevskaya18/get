TEST(MatrixTest, CheckSolution) {
    Matrix<double> m{{2, 1}, {5, 7}};
    subvector<double> results{11, 13};
    subvector<double> solution{7, -3};
    EXPECT_FALSE(check_solution(m, results, solution));
}
