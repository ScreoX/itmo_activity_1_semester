cmake_minimum_required(VERSION 3.26)
project(c C)

set(CMAKE_C_STANDARD 17)

add_executable(c main.c
        header.h
        for_11_lab.c
)
