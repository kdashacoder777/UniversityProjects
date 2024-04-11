#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include <cstdlib>
#include <chrono>

#ifndef UNIVERWORK2024_COMMON_H
#define UNIVERWORK2024_COMMON_H

#define COEF 0.000000001

void saveVectorToFile(int n, const std::vector<double> &vec, const std::vector<std::vector<double>> &mat, int &id) {
    std::ofstream file("vectorData_id_" + std::to_string(id) + ".txt");

    file << n << std::endl; // writing the size of vector
    for (int i = 0; i < n; ++i) {
        file << vec[i] << std::endl; // writing elements of vector
    }

    file.close();
}

void saveMatrixToFile(int n, const std::vector<std::vector<double>> &mat, int &id) {
    std::ofstream file("matrixData_id_" + std::to_string(id) + ".txt");

    file << n << std::endl; // writing the size of matrix

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << mat[i][j] << std::endl; // writing elements of matrix
        }
    }
    file.close();
}

void readVectorFromFile(int &n, std::vector<double> &vec, int &id) {
    std::ifstream file("vectorData_id_" + std::to_string(id) + ".txt");

    file >> n; // reading the size of vector/matrix

    for (int i = 0; i < n; ++i) {
        file >> vec[i]; // reading elements of vector
    }

    file.close();
}

void readMatrixFromFile(int &n, std::vector<std::vector<double>> &mat, int &id) {
    std::ifstream file("matrixData_id_" + std::to_string(id) + ".txt");

    file >> n; // reading the size of vector/matrix

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file >> mat[i][j]; // reading elements of matrix
        }
    }

    file.close();
}

void generateVector(int n, std::vector<double> &vec) {
    for (int i = 0; i < n; ++i) {
        vec[i] = (double)(rand())/RAND_MAX; // generating random vector
    }
}

void intGenerateVector(int n, int firstValue, int lastValue, std::vector<int> &vec) {
    vec.resize(n);
    for (int i = 0; i < n; ++i) {
        vec[i] = firstValue + rand() % lastValue;; // generating random int vector
    }
}

void generateMatrix(int n, std::vector<std::vector<double>> &mat) {

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            mat[i][j] = (double)(rand())/RAND_MAX; // generating random matrix
        }
    }
}

template<typename Type>
void printVector(int &n, const std::vector<Type> &vec) {
    if (n < 50) {
        std::cout << "Vector[" << n << "]:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
}

void printMatrix(int &n, const std::vector<std::vector<double>> &mat) {
    if (n < 50) {
        std::cout << std::endl << "Matrix[" << n << "][" << n << "]:" << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

#endif //UNIVERWORK2024_COMMON_H
