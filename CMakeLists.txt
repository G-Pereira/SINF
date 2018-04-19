cmake_minimum_required(VERSION 2.8)
project(SINF)

find_package (Threads)

add_executable(SINF src/main.c)

target_link_libraries (SINF m ${CMAKE_THREAD_LIBS_INIT})