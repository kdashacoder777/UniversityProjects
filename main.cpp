#include "task1.h"
#include "task2.h"


int main() {

    setlocale(LC_ALL, "Russian");
    
    std::cout << "Task 1 run" << std::endl;
    task1();
    std::cout << "Task 1 completed successfully" << std::endl;

    std::cout << "Task 2 start" << std::endl;
    task2();
    std::cout << "Task 2 completed successfully" << std::endl;

    std::cout << "Task 3 launch" << std::endl;
    task3();
    std::cout << "Task 3 completed successfully" << std::endl;

    return 0;
}
