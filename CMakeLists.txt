cmake_minimum_required(VERSION 3.22.1)
project(UniverWork2024)

set(CMAKE_CXX_STANDARD 17)

# Добавляем флаги компилятора OpenMP
find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()

add_executable(UniverWork2024 main.cpp)
