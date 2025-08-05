cmake_minimum_required(VERSION 3.18)
project(
    car_project
    VERSION 1.0.0
    DESCRIPTION "Car and Lorry classes implementation"
    LANGUAGES CXX
)

# Установка стандарта C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Установка типа сборки - Debug
set(CMAKE_BUILD_TYPE Debug)

# Создание исполняемого файла
add_executable(car_project main.cpp)
