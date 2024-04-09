#include <iostream>
#include <vector>
#include <omp.h>
#include <fstream>
#include <cstdlib>
#include <chrono>

#define COEF 0.000000001

void matrixVectorMultiplication(int n, int numThreads, std::vector<std::vector<double>>& matrix,
                                std::vector<double>& vector, std::vector<double>& result) {
    omp_set_num_threads(numThreads);
    double sum;
#pragma omp parallel for private(sum)
    for (int i = 0; i < n; ++i)
    {
        sum = 0;
        for (int j = 0; j < n; ++j)
        {
//            int threadId = omp_get_thread_num();
//            std::cout << "Hello from thread " << threadId << std::endl;
            sum +=  COEF * matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}

double matrixVectorMultiplicationParallelRunTime(int n, int numThreads, std::vector<std::vector<double>>& mat,
                                                 std::vector<double>& vec, std::vector<double>& result) {
    auto start = std::chrono::high_resolution_clock::now();
    matrixVectorMultiplication(n, numThreads, mat, vec, result);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    std::cout << "Программа выполнена для " << numThreads << " потока(ов) за "<< duration_ms.count() << " миллисекунд" << std::endl;
    return duration_ms.count();
}

void saveVectorToFile(int n, std::vector<double> &vec, std::vector<std::vector<double>> &mat, int &id) {
    std::ofstream file("vectorData_id_" + std::to_string(id) + ".txt");

    file << n << std::endl; // writing the size of vector
    for (int i = 0; i < n; ++i) {
        file << vec[i] << std::endl; // writing elements of vector
    }

    file.close();
}

void saveMatrixToFile(int n, std::vector<std::vector<double>> &mat, int &id) {
    std::ofstream file("matrixData_id_" + std::to_string(id) + ".txt");

    file << n << std::endl; // writing the size of matrix

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            file << mat[i][j] << std::endl; // writing elements of matrix
        }
    }
    file.close();
}

void readVectorFromFile(int &n, std::vector<double> &vec, std::vector<std::vector<double>> &mat, int &id) {
    std::ifstream file("vectorData_id_" + std::to_string(id) + ".txt");

    file >> n; // reading the size of vector/matrix

    for (int i = 0; i < n; ++i) {
        file >> vec[i]; // reading elements of vector
    }

    file.close();
}

void readMatrixFromFile(int &n, std::vector<double> &vec, std::vector<std::vector<double>> &mat, int &id) {
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

void generateMatrix(int n, std::vector<std::vector<double>> &mat) {

     for (int i = 0; i < n; ++i) {
         for (int j = 0; j < n; ++j) {
             mat[i][j] = (double)(rand())/RAND_MAX; // generating random matrix
         }
     }
}

void printVector(int &n, std::vector<double> &vec) {
    if (n < 50) {
        std::cout << "Vector[" << n << "]:" << std::endl;
        for (int i = 0; i < n; ++i) {
            std::cout << vec[i] << " ";
        }
        std::cout << std::endl;
    }
}

void printMatrix(int &n, std::vector<std::vector<double>> &mat) {
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


int main() {
    setlocale(LC_ALL, "Russian");
    double runTimeOneThread = 0.0;
    std::vector<double> vec;
    std::vector<std::vector<double>> mat;
    std::vector<double> vecResult;

    std::ofstream file("statisticOfRunTimeMultiMatrixVectorThreads.csv");
    file << "Razmer obektov;"
            "Posledovatelnyj algoritm (vremya);"
            "2 processa (vremya);"
            "2 processa (izmenenie);"
            "4 processa (vremya);"
            "4 processa (izmenenie);"
            "8 processov (vremya);"
            "8 processov (izmenenie);"
            "16 processov (vremya);"
            "16 processov (izmenenie);"
         << std::endl;

    int maxSize = 30000;
    std::vector<int> listOfThreads = {2, 4, 8, 16};
    std::vector<int> listSizeOfObjects = {2000, 5000, 10000, 15000, maxSize};
            std::vector<double> listOfRunTimes = {};

    int sizeReserve = maxSize + 1000;
    vec.reserve(sizeReserve);
    vecResult.reserve(sizeReserve);
    mat.reserve(sizeReserve);
    for (int i = 0; i < sizeReserve; ++i) {
        mat[i].reserve(sizeReserve);
    }

    for (auto &sizeOfObject: listSizeOfObjects) {

        // generating random vector
        generateVector(sizeOfObject, vec);
        // generating random matrix
        generateMatrix(sizeOfObject, mat);

        std::cout << "Размер объекта n = " << sizeOfObject << std::endl;
        // matrix Vector Multiplication for 1 thread
        runTimeOneThread = matrixVectorMultiplicationParallelRunTime(sizeOfObject, 1, mat, vec, vecResult);

        // matrix Vector Multiplication for list of thread
        for (auto &numOfThread: listOfThreads) {
            listOfRunTimes.push_back(matrixVectorMultiplicationParallelRunTime(sizeOfObject, numOfThread, mat, vec, vecResult));
        }

        std::cout << "Запись в файл .. " << std::endl;
        // output statistic
        file << std::to_string(sizeOfObject) << ";";
        file << runTimeOneThread << ";";
        for (auto &runTimeOfThread: listOfRunTimes) {
            file << runTimeOfThread << ";" << runTimeOneThread - runTimeOfThread << ";" ;
        }
        file << std::endl;
        listOfRunTimes = {};
    }
    file.close();

    return 0;
}
