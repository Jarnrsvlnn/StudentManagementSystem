cmake_minimum_required(VERSION 3.31)
project(StudentManagementSystem C)

set(CMAKE_C_STANDARD 17)

add_executable(StudentManagementSystem main.c
        student_functions.c
        student_functions.h)
