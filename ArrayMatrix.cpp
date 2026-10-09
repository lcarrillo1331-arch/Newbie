/*
How the Single-Index Hack Works

When you write mat[r][c], the compiler parses it from
left to right as (mat[r])[c].mat[r] triggers your
overloaded operator[](size_t row), which performs
bounds checking on the row and returns a memory address
(T*) pointing exactly to the first element of that row.
The remaining [c] evaluates natively against that
returned pointer using standard C++ pointer arithmetic
(pointer + c), shifting right to the correct column.
Note: While elegant, a downside to this raw-pointer
method is that the secondary [c] step bypasses your
class logic, meaning column-level bounds checking cannot
be safely handled at runtime.
*/

#include "ArrayMatrix.h"
int main() {
    // TODO: Create matrices to demonstrate use of ALL
    //       methods in ArrayMatrix class.
    try {
        ArrayMatrix<int> matrixA(2, 3);
        matrixA[0][0] = 1;
        matrixA[0][1] = 2;
        matrixA[0][2] = 3;
        matrixA[1][0] = 4;
        matrixA[1][1] = 5;
        matrixA[1][2] = 6;

        // Demonstrate print()
        matrixA.print();

        // Demonstrate rows() and cols()
        std::cout << matrixA.rows() << "\n";
        std::cout << matrixA.cols() << "\n";

        // Demonstrate copy constructor
        ArrayMatrix<int> copiedMatrix(matrixA);
        copiedMatrix.print();

        // Demonstrate copy assignment operator
        ArrayMatrix<int> assignedMatrix(2, 3);
        assignedMatrix = matrixA;
        assignedMatrix.print();

        // Demonstrate const operator[]
        const ArrayMatrix<int>& readOnlyMatrix = matrixA;
        std::cout << readOnlyMatrix[0][1] << "\n";

        // Create another 2x3 matrix for addition
        ArrayMatrix<int> matrixC(2, 3, 10);

        // Demonstrate operator+
        ArrayMatrix<int> sum = matrixA + matrixC;
        std::cout << sum.print();

        // Create a 3x2 matrix for multiplication
        ArrayMatrix<int> matrixB(3, 2);
        matrixB[0][0] = 1;
        matrixB[0][1] = 2;
        matrixB[1][0] = 3;
        matrixB[1][1] = 4;
        matrixB[2][0] = 5;
        matrixB[2][1] = 6;

        // Demonstrate operator*
        ArrayMatrix<int> product = matrixA * matrixB;
        std::cout << product.print();


    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Use streams to init and output
    // Create a 2x3 matrix for user input
    ArrayMatrix<int> mat(2, 3);

    // Prompt user input using standard stream extraction (cin)
    std::cout << "Enter 6 integer values for a 2x3 matrix (separated by spaces or newlines):\n";
    // TODO: cin statement
    std::cin >> mat;

    // Output the matrix formatting cleanly via custom insertion stream
    std::cout << "\nYou entered the following matrix:\n";
    // TODO: cout statement
    std::cout << mat;

    return 0;
}
