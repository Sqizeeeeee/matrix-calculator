#include "matrix.h"
#include <iostream>

int main() {
    std::cout << "=== Matrix Calculator ===" << std::endl;

    try {
        Matrix A = create_matrix(2, 2);
        A.data[0][0] = 1.0; A.data[0][1] = 2.0;
        A.data[1][0] = 3.0; A.data[1][1] = 4.0;

        Matrix B = create_matrix(2, 2);
        B.data[0][0] = 5.0; B.data[0][1] = 6.0;
        B.data[1][0] = 7.0; B.data[1][1] = 8.0;


        std::cout << "Matrix A: " << "\n";
        print_matrix(A);
        std::cout << '\n';

        std::cout << "Matrix B: " << "\n";
        print_matrix(B);
        std::cout << '\n';

        std::cout << "A + B: " << "\n";
        Matrix Res = matrix_add(A, B);
        print_matrix(Res);
        std::cout << '\n';

        std::cout << "A * B: " << '\n';
        Matrix res1 = matrix_multiply(A, B);
        print_matrix(res1);
        std::cout << '\n';


        std::cout << "transponse matrix:" << '\n';
        Matrix res2 = matrix_transpose(A);
        print_matrix(res2);
        std::cout << '\n';

        free_matrix(A);
        free_matrix(B);
        free_matrix(Res);
        free_matrix(res1);
        free_matrix(res2);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}