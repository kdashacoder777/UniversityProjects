#include <cmath>
#include "common.h"

#ifndef UNIVERWORK2024_TASK3_H
#define UNIVERWORK2024_TASK3_H

void DecompositionMainElementLU(const std::vector<std::vector<double>>& A,
                                std::vector<std::vector<double>>& L,
                                std::vector<std::vector<double>>& U) {
    int n = A.size();
    std::vector<double> vecNorm(n, 0);
    if (L.size() != U.size() && n != U.size()) {
        std::cout << "Error DecompositionMainElementLU(A, L, U)! Size of objects are not equal!" << std::endl;
        std::cout << "L.size() = " << L.size()  << ", U.size() = "<< U.size()  << ", A.size() = " << A.size() << std::endl;
        throw std::invalid_argument("A.size() != L.size() != U.size");
    }

    U = A;

    for (int k = 0; k < n - 1 ; ++k) {
        // Находим индекс главного элемента в столбце k
        int pivot = k;
        double max = U[k][k];
        for (int i = k + i; i < n; ++i) {
            if (abs(U[i][k]) > abs(U[pivot][k])) {
                pivot = i;
                max = U[i][k];
            }
        }

        if (U[pivot][k] == 0) {
            throw std::runtime_error("Matrica virojdena");
        } else {
            if (pivot != k) {
                // std::cout << " swap k = " << k << "pivot = " << pivot << std::endl;
                for (int j = 0; j < n; ++j) {
                    std::swap(U[pivot][j], U[k][j]);
                    std::swap(L[pivot][j], L[k][j]);
                }
            }
        }

        for (int i = k + 1; i < n; ++i) {
            // Вычисляем коэффициенты для L и U
            double factor = U[i][k] / max;
            L[i][k] = factor;
            for (int j = k; j < n; ++j) {
                U[i][j] -= factor * U[k][j];
            }
        }
    }
//    LU
//        for(int i = 0; i < n; i++)
//            for(int j = i; j < n; j++) {
//                L[j][i] = U[j][i] / U[i][i];
//            }
//
//        for(int k = 1; k < n; k++)
//        {
//            for(int i = k-1; i < n; i++)
//                for(int j = i; j < n; j++) {
//                    L[j][i] = U[j][i] / U[i][i];
//                }
//
//            for(int i = k; i < n; i++) {
//                for (int j = k - 1; j < n; j++) {
//                    U[i][j] = U[i][j] - L[i][k - 1] * U[k - 1][j];
//                }
//            }
//        }
//

    // Заполняем диагональные элементы L единицами
    for (int i = 0; i < n; ++i) {
        L[i][i] = 1.0;
    }
}

std::vector<std::vector<double>> MatrixMultiplication(const std::vector<std::vector<double>>& A,
                                                      const std::vector<std::vector<double>>& B) {
    if (A.size() != B.size()) {
        std::cout << "Error MatrixMultiplication(A, B)! Size of objects are not equal!" << std::endl;
        std::cout << "v1.size() = " << A.size()  << ", v2.size() = " <<  B.size() << std::endl;
        throw std::invalid_argument("v1.size() != v2.size");
    }

    int m = A.size();
    int n = B[0].size();
    int p = B.size();

    std::vector<std::vector<double>> result(m, std::vector<double>(n, 0.0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < p; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

void MatrixVectorMultiplication(int n, const std::vector<std::vector<double>>& matrix,
                                const std::vector<double>& vector, std::vector<double>& result) {
    double sum;
    for (int i = 0; i < n; ++i)
    {
        sum = 0;
        for (int j = 0; j < n; ++j) {
            sum +=  matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}


double Residual(const std::vector<double>& v1, const std::vector<double>& v2) {
    if (v1.size() != v2.size()) {
        std::cout << "Error residual(v1, v2)! Size of objects are not equal!" << std::endl;
        std::cout << "v1.size() = " << v1.size()  << ", v2.size() = " << v2.size() << std::endl;
        throw std::invalid_argument("v1.size() != v2.size");
    }

    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        double diff = v1[i] - v2[i];
        sum += diff * diff;
    }
    return std::sqrt(sum);
}

double DecompositionMainElementLUSolution(const std::vector<std::vector<double>>& A,
                                    std::vector<std::vector<double>>& L,
                                    std::vector<std::vector<double>>& U,
                                    double &residual,
                                    double &runtime) {
    auto start = std::chrono::high_resolution_clock::now();
    DecompositionMainElementLU(A, L, U);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    runtime = duration_ms.count();

    int n = A.size();
    std::vector<double> unitVector(n, 1.0);
    std::vector<double> vecResA(n);
    std::vector<double> vecResUx(n);
    std::vector<double> vecResLUx(n);

    MatrixVectorMultiplication(n, A, unitVector, vecResA);
    MatrixVectorMultiplication(n, U, unitVector, vecResUx);
    MatrixVectorMultiplication(n, L, vecResUx, vecResLUx);

    residual = Residual(vecResA, vecResLUx);

    std::cout << "Results: decomposition A = LU: " << std::endl;
    std::cout << "n            :"  << A.size() << std::endl;
    std::cout << "residual     :"  << residual << std::endl;
    std::cout << "run time(ms) :"  << runtime << std::endl;
    return runtime;
}

inline void ResizeMatrix(int n, std::vector<std::vector<double>> &mat) {
    mat.resize(n);
    for (int i = 0; i < n; ++i) {
        mat[i].resize(n);
        for (int j = 0; j < n; ++j) {
            mat[i][j] = 0.0;
        }
    }
}

void printMatrixName(std::string nameMat, const std::vector<std::vector<double>> &mat) {
    int n = mat.size();
    if (n < 50) {
        std::cout << std::endl << nameMat + "[" << n << "][" << n << "]:" << std::endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cout << mat[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

template<typename Type>
void printVectorName(std::string nameVec, const std::vector<Type> &vec) {
    int n = nameVec.size();
    if (n < 50) {
        std::cout << nameVec + "[" << n << "]:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
}


void task3() {

    double residual, runtime = 0.0;
    std::vector<double> vec;
    std::vector<std::vector<double>> A;
    std::vector<std::vector<double>> L;
    std::vector<std::vector<double>> U;

    int minSize = 1000;
    int maxSize = 6000;
    std::vector<int> listSizeOfObjects = {minSize, 2 * minSize, 3 * minSize, 4 * minSize, maxSize};

    // Example 1 solution
    std::cout << "Exmaple 1" << std::endl;
    std::vector<std::vector<double>> Aex = {{2., -1., 1.},
                                            {-3., -1., 4.},
                                            {-1., 1., 3.}};
    std::vector<std::vector<double>> Lex = {{1, 0, 0},
                                            {-1.5, 1, 0},
                                            {-0.5, 2, 1}};
    std::vector<std::vector<double>> Uex = {{2, -1, 1},
                                            {0, -0.5, 2.5},
                                            {0, 0, 2}};
    printMatrixName("Aex", Aex);
    printMatrixName("Lex", Lex);
    printMatrixName("Uex", Uex);
    ResizeMatrix(3, L);
    ResizeMatrix(3, U);
    DecompositionMainElementLUSolution(Aex, L, U, residual, runtime);
    printMatrixName("Lres", L);
    printMatrixName("Ures", U);

    // Example 2 solution
    std::cout << "Exmaple 2" << std::endl;
    int size = 100;
    ResizeMatrix(size, A);
    generateMatrix(size, A);
    ResizeMatrix(size, L);
    ResizeMatrix(size, U);

    DecompositionMainElementLUSolution(A, L, U, residual, runtime);
    printMatrixName("Lres", L);
    printMatrixName("Ures", U);
}

#endif //UNIVERWORK2024_TASK3_H
