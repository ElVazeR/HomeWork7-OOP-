#include <iostream>
#include <cstdlib>
#include <ctime>

template <typename T>
class Matrix {
private:
    T** data;
    size_t rows;
    size_t cols;

public:
    Matrix(size_t rows, size_t cols);
    Matrix(const Matrix& other);
    Matrix(Matrix&& other) noexcept;
    ~Matrix();

    void Keyboard();
    void Random();
    void print() const;
    T getMax() const;
    T getMin() const;

    

    Matrix operator+(const Matrix& other) const;
};

template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : rows(rows), cols(cols) {
    data = new T * [rows];
    for (size_t i = 0; i < rows; i++) {
        data[i] = new T[cols];
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    data = new T * [rows];
    for (size_t i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for (size_t j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix&& other) noexcept {
    std::swap(data, other.data);
    std::swap(rows, other.rows);
    std::swap(cols, other.cols);
}

template <typename T>
Matrix<T>::~Matrix() {
    for (size_t i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

template <typename T>
void Matrix<T>::Keyboard() {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << "Enter element [" << i << "][" << j << "]: ";
            std::cin >> data[i][j];
        }
    }
}

template <typename T>
void Matrix<T>::Random() {
    srand(time(NULL));
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            data[i][j] = rand() % 100;
        }
    }
}

template <typename T>
void Matrix<T>::print() const {
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            std::cout << data[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <typename T>
T Matrix<T>::getMax() const {
    T max = data[0][0];
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (data[i][j] > max) {
                max = data[i][j];
            }
        }
    }
    return max;
}

template <typename T>
T Matrix<T>::getMin() const {
    T min = data[0][0];
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            if (data[i][j] < min) {
                min = data[i][j];
            }
        }
    }
    return min;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix& other) const {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Матрицы имеют разные размеры");
    }

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "Russian");

    Matrix<int> m1(2, 3);
    m1.Random();
    std::cout << " Matrix 1: " << std::endl;
    m1.print();

    Matrix<int> m2(2, 3);
    m2.Random();
    std::cout << "Matrix 2:" << std::endl;
    m2.print();

    Matrix<int> sum = m1 + m2;
    std::cout << "Sum of matrices:" << std::endl;
    sum.print();

    return 0;
}