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



    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    // Use streams to init and output
    // Create a 2x3 matrix for user input
    ArrayMatrix<int> mat(2, 3);

    // Prompt user input using standard stream extraction (cin)
    std::cout << "Enter 6 integer values for a 2x3 matrix (separated by spaces or newlines):\n";
    // TODO: cin statement

    // Output the matrix formatting cleanly via custom insertion stream
    std::cout << "\nYou entered the following matrix:\n";
    // TODO: cout statement

    return 0;
}