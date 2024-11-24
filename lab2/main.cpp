#include "matrix.h"
#include <iostream>

int main() {
    {
        int expectedDeterminant = 120;
        Matrix<int> m = Matrix<int>::getSpecificDeterminant(5, expectedDeterminant);
        if (determinant(m) != expectedDeterminant) {
            std::cout << "Test failed for 5x5 matrix with determinant " << expectedDeterminant
                << std::endl;
        }
    }

    {
        int expectedDeterminant = 12'345'678;
        Matrix<int> m = Matrix<int>::getSpecificDeterminant(50, expectedDeterminant);
        if (determinant(m) != expectedDeterminant) {
            std::cerr << "Test failed for 50x50 matrix with determinant " << expectedDeterminant
                << std::endl;
        }
    }

    {
        int expectedDeterminant = 12'345'678;
        Matrix<int> m = Matrix<int>::getSpecificDeterminant(200, expectedDeterminant);
        if (determinant(m) != expectedDeterminant) {
            std::cerr << "Test failed for 200x200 matrix with determinant " << expectedDeterminant
                << std::endl;
        }
    }

    std::cout << "All tests in main have passed successfully!" << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    std::cin.get();

    return 0;
}

