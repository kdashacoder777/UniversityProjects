#include "common.h"

#ifndef UNIVERWORK2024_TASK2_H
#define UNIVERWORK2024_TASK2_H


struct Compare { int val; int index; };
#pragma omp declare reduction(maximum : \
                              struct Compare : \
                              omp_out = omp_in.val > omp_out.val ? omp_in : omp_out) \
                              initializer(omp_priv=omp_orig)

void selectionSort(int n, std::vector<int>& arr)
{
    for (int i = n - 1; i > 0; --i) {
        struct Compare max;
        max.val = arr[i];
        max.index = i;
#pragma omp parallel for reduction(maximum:max)
        for (int j = i - 1; j >= 0; --j)
        {
            if (arr[j] > max.val)
            {
                max.val = arr[j];
                max.index = j;
            }
        }
        int tmp = arr[i];
        arr[i] = max.val;
        arr[max.index] = tmp;
    }
}

double selectionSortParallelRunTime(int n, int numThreads, std::vector<int>& vec) {
    omp_set_num_threads(numThreads);
    auto start = std::chrono::high_resolution_clock::now();
    selectionSort(n, vec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    std::cout << "Программа выполнена для " << numThreads << " потока(ов) за "<< duration_ms.count() << " миллисекунд" << std::endl;
    return duration_ms.count();
}

void quickSort(int* v, int left, int right)
{
    long long i = left, j = right;
    long long pivot = v[(i + j) / 2];

    while (i <= j)
    {
        while (v[i] < pivot)i++;
        while (v[j] > pivot)j--;
        if (i <= j)
        {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }
    if (j > left) quickSort(v, left, j);
    if (i < right) quickSort(v, i, right);
}

void multiThreadQuickSort(int *v, int low, int high) {
    int i = low;
    int j = high;
    int pivot = v[(low + high) / 2];
    while (i <= j) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
        if (i <= j) {
            std::swap(v[i], v[j]);
            i++;
            j--;
        }
    }
#pragma omp parallel sections shared(v, low, i, j, high)
    {
#pragma omp section
        {
            if (j > low) quickSort(v, low, j);
        }
#pragma omp section
        {
            if (i < high) quickSort(v, i, high);
        }
    }
}


double quickSortRunTime(int n, int numThreads, std::vector<int>& vec) {
    omp_set_num_threads(numThreads);
    auto start = std::chrono::high_resolution_clock::now();
    multiThreadQuickSort(vec.data(), 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    std::cout << "Программа выполнена для " << numThreads << " потока(ов) за "<< duration_ms.count() << " миллисекунд" << std::endl;
    return duration_ms.count();
}

void mergeSort(int *X, int n, int *tmp)
{
    if (n < 2) return;
#pragma omp task shared(X) if (n > 14)
    mergeSort(X, n/2, tmp);

#pragma omp task shared(X) if (n > 14)
    mergeSort(X+(n/2), n-(n/2), tmp + n/2);

#pragma omp taskwait
    int i = 0;
    int j = n/2;
    int ti = 0;

    while (i<n/2 && j<n) {
        if (X[i] < X[j]) {
            tmp[ti] = X[i];
            ti++; i++;
        } else {
            tmp[ti] = X[j];
            ti++; j++;
        }
    }
    while (i<n/2) { /* finish up lower half */
        tmp[ti] = X[i];
        ti++; i++;
    }
    while (j<n) { /* finish up upper half */
        tmp[ti] = X[j];
        ti++; j++;
    }

    std::copy(tmp, tmp + n, X);
}

double mergeSortRunTime(int n, int numThreads, std::vector<int>& vec) {
    omp_set_num_threads(numThreads);
    std::vector<int> temp;
    temp.reserve(n);
    auto start = std::chrono::high_resolution_clock::now();
#pragma omp parallel
    {
        #pragma omp single
        mergeSort(vec.data(), n, temp.data());
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration_ms = end - start;
    std::cout << "Программа выполнена для " << numThreads << " потока(ов) за "<< duration_ms.count() << " миллисекунд" << std::endl;
    return duration_ms.count();
}

void task2() {

    std::vector<int> vec;
    int maxSize = 30000;
    std::vector<int> listOfThreads = {2, 4, 8, 16};
    std::vector<int> listSizeOfObjects = {2000, 5000, 10000, 15000, maxSize};
    std::vector<double> listOfRunTimes = {};

    int sizeReserve = maxSize + 1000;
    vec.reserve(sizeReserve);

    int n = 100000;
    std::cout << "Размер объекта n = " << n << std::endl;

    std::cout << "Сортировка выбором " << std::endl;
    intGenerateVector(n, 0, n, vec);
    printVector<int>(n, vec);
    selectionSortParallelRunTime(n, 1, vec);
    printVector<int>(n, vec);

    std::cout << "<Быстрая сортировка" << std::endl;
    intGenerateVector(n, 0, n, vec);
    printVector<int>(n, vec);
    quickSortRunTime(n, 1, vec);
    printVector<int>(n, vec);

    std::cout << "Слиянием сортировка" << std::endl;
    intGenerateVector(n, 0, n, vec);
    printVector<int>(n, vec);
    mergeSortRunTime(n, 1, vec);
    printVector<int>(n, vec);
}

#endif //UNIVERWORK2024_TASK2_H
