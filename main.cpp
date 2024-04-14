#include "task1.h"
#include "task2.h"


int main() {

    setlocale(LC_ALL, "Russian");

    std::cout << "Задание 1 запуск" << std::endl;
    task1();
    std::cout << "Задание 1 успешно закончено" << std::endl;

    std::cout << "Задание 2 запуск" << std::endl;
    task2();
    std::cout << "Задание 2 успешно закончено" << std::endl;

    std::cout << "Задание 3 запуск" << std::endl;
    task3();
    std::cout << "Задание 3 успешно закончено" << std::endl;


    return 0;
}
