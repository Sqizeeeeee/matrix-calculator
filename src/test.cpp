#include "matrix.h"
#include <iostream>
#include <cassert>

void test_create_and_free() {
    std::cout << "Test 1: Create and free matrix...";
    Matrix m = create_matrix(3, 3);
    assert(m.rows == 3);
    assert(m.cols == 3);
    assert(m.data != nullptr);
    free_matrix(m);
    std::cout << "PASSED" << "\n";
}

void test_matrix_addition() {
    std::cout << "Test 2: Matrix addition...";
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(2, 2);

    A.data[0][0] = 1; A.data[0][1] = 2;
    A.data[1][0] = 3; A.data[1][1] = 4;
    
    B.data[0][0] = 5; B.data[0][1] = 6;
    B.data[1][0] = 7; B.data[1][1] = 8;


    Matrix Res = matrix_add(A, B);

    assert(Res.data[0][0] == 6);
    assert(Res.data[0][1] == 8);
    assert(Res.data[1][0] == 10);
    assert(Res.data[1][1] == 12);

    free_matrix(A);
    free_matrix(B);
    free_matrix(Res);

    std::cout << "PASSED" << "\n";
}

void test_invalid_addition() {
    std::cout << "Test 3: Invalid addition (should throw exception)... ";
    Matrix A = create_matrix(2, 2);
    Matrix B = create_matrix(3, 3); // Несовместимые размеры!
    
    try {
        Matrix result = matrix_add(A, B);
        assert(false); // Не должно сюда попасть!
    } catch (const std::exception& e) {
        // Ожидаемое поведение - исключение
        std::cout << "PASSED (" << e.what() << ")" << std::endl;
    }
    
    free_matrix(A);
    free_matrix(B);
}

void test_matrix_symmetric() {
    std::cout << "Test 4: Symmetric matrix check... ";
    
    // Тест 1: Симметричная матрица
    Matrix symm = create_matrix(3, 3);
    symm.data[0][0] = 1.0; symm.data[0][1] = 2.0; symm.data[0][2] = 3.0;
    symm.data[1][0] = 2.0; symm.data[1][1] = 4.0; symm.data[1][2] = 5.0;
    symm.data[2][0] = 3.0; symm.data[2][1] = 5.0; symm.data[2][2] = 6.0;
    
    assert(matrix_is_symmetric(symm, 0.0001) == true);
    
    // Тест 2: Несимметричная матрица
    Matrix non_symm = create_matrix(2, 2);
    non_symm.data[0][0] = 1.0; non_symm.data[0][1] = 2.0;
    non_symm.data[1][0] = 3.0; non_symm.data[1][1] = 4.0; // 2.0 != 3.0
    
    assert(matrix_is_symmetric(non_symm, 0.0001) == false);
    
    // Тест 3: Неквадратная матрица
    Matrix rectangular = create_matrix(2, 3);
    assert(matrix_is_symmetric(rectangular, 0.0001) == false);
    
    free_matrix(symm);
    free_matrix(non_symm);
    free_matrix(rectangular);
    std::cout << "PASSED" << std::endl;
}


int main() {
    std::cout << "=== Running Matrix Unit Tests ===" << std::endl;
    
    test_create_and_free();
    test_matrix_addition();
    test_invalid_addition();
    test_matrix_symmetric();
    
    std::cout << "=== All tests passed! ===" << std::endl;
    return 0;
}