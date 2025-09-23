#include "matrix.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Создат новую матрицу с заданными размерами
 * @param rows Количество строк (должно быть > 0)
 * @param cols Количество столбцов (должно быть > 0)
 * @return Matrix Структура Matrix с выделенной памятью
 * @exception std::invalid_argument Если размеры не правильные
 * @exception std::bad_alloc Если не удалось выделить память
 */
 Matrix create_matrix(int rows, int cols) {
    if (rows <= 0 || cols <= 0) {
        throw std::invalid_argument("Matrix parameters must be positive");
    }

    Matrix mat;
    mat.rows = rows;
    mat.cols = cols;

    mat.data = new double*[rows];
    if (mat.data == nullptr) {
        throw std::bad_alloc();
    }

    for (int i = 0; i < rows; i++) {
        mat.data[i] = new double[cols];

        if (mat.data[i] == nullptr) {
            for (int j = 0; j < i; j++) {
                delete[] mat.data[j];
            }
            delete[] mat.data;
            throw std::bad_alloc();
        }

        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = 0.0;
        }
    }

    return mat;
 }

 /**
  * @brief Освобождает память, занятую матрицей
  * @param m Матрица, память которую нужно освободить
  */
void free_matrix(Matrix m) {
    if (m.data == nullptr) {
        return;
    }

    for (int i = 0; i < m.rows; i++) {
        if (m.data[i] != nullptr) {
            delete[] m.data[i];
        }
    }

    delete[] m.data;
}

/**
 * @brief Сложение двух матриц
 * @param a Первая матрица
 * @param b Вторая матрица
 * @return Matrix Результирующая матрица
 * @exception std::invalid_argument Если размеры матриц не совпадают
 */
Matrix matrix_add(Matrix a, Matrix b) {
    if (a.rows != b.rows || a.cols != b.cols) {
        throw std::invalid_argument("Parameters must match in 2 matrix");
    }

    Matrix result = create_matrix(a.rows, a.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < a.cols; j++) {
            result.data[i][j] = a.data[i][j] + b.data[i][j];
        }
    }
    return result;
}

/**
 * @brief Умножение двух матриц
 * @param a Первая матрица (размер M×N)
 * @param b Вторая матрица (размер N×K)
 * @return Matrix Результирующая матрица (размер M×K)
 * @exception std::invalid_argument Если количество столбцов A не равно количеству строк B
 */
Matrix matrix_multiply(Matrix a, Matrix b) {
    if (a.cols != b.rows) {
        throw std::invalid_argument("Number of columns in A must be equal of rows in B");
    }

    Matrix result = create_matrix(a.rows, b.cols);

    for (int i = 0; i < a.rows; i++) {
        for (int j = 0; j < b.cols; j++) {
            result.data[i][j] = 0.0;
            for (int k = 0; k < a.cols; k++) {
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}

/**
 * @brief Транспонирование матрицы
 * @param m Исходная матрица
 * @return Matrix Транспонированная матрица
 */
Matrix matrix_transpose(Matrix m) {
    Matrix result = create_matrix(m.cols, m.rows);

    for (int i = 0; i < m.rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            result.data[j][i] = m.data[i][j];
        }
    }

    return result;
}


/**
 * @brief Вывод матрицы в консоль в форматированном виде
 * @param m Матрица для вывода
 */
void print_matrix(Matrix m) {
    if (m.data == nullptr || m.rows <= 0 || m.cols <= 0) {
        std::cout << "[Empty matrix]" << std::endl;
    }

    std::cout << std::fixed << std::setprecision(2);

    for (int i = 0; i < m.rows; i++) {
        std::cout << "[ ";
        for (int j = 0; j < m.cols; j++) {
            std::cout << std::setw(6) << m.data[i][j];
            if (j < m.cols - 1) {
                std::cout << " ";
            }
        }
        std::cout << " ]" <<std::endl;
    }
}

/**
 * @brief Создание матрицы из одномерного массива
 * @param data Указатель на массив данных
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Matrix Новая матрица с данными из массива
 */
Matrix matrix_from_array(double* data, int rows, int cols) {
    Matrix mat = create_matrix(rows, cols);

    int index = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mat.data[i][j] = data[index++];
        }
    }

    return mat;
}

/**
 * @brief Проверяет, является ли матрица симметричной
 * @param m Матрица для проверки
 * @param tolerance Допустимая погрешность для сравнения чисел с плавающей точкой
 * @return true если матрица квадратная и симметричная, false в противном случае
 * 
 * @note Матрица считается симметричной, если она равна своей транспонированной версии:
 *       A[i][j] == A[j][i] для всех i, j
 * @note Для неквадратных матриц всегда возвращается false
 */
bool matrix_is_symmetric(Matrix m, double tolerance) {
    // Неквадратные матрицы не могут быть симметричными
    if (m.rows != m.cols) {
        return false;
    }
    
    // Проверка валидности матрицы
    if (m.data == nullptr || m.rows <= 0) {
        return false;
    }
    
    // Проверяем симметричность: A[i][j] == A[j][i] для всех i, j
    for (int i = 0; i < m.rows; i++) {
        for (int j = i + 1; j < m.cols; j++) { // Начинаем с j = i+1 для оптимизации
            double diff = m.data[i][j] - m.data[j][i];
            if (diff < 0) diff = -diff; // Берем модуль разности
            
            if (diff > tolerance) {
                return false; // Нашли несимметричные элементы
            }
        }
    }
    
    return true; // Все элементы симметричны
}
