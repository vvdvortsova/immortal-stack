cmake_minimum_required(VERSION 3.15)
project(immortal_stack C)
add_compile_options( -Wall -Wextra)

set(CMAKE_C_STANDARD 11)

add_executable(immortal_stack main.c src/stack.c src/stack.h src/templates.h src/all_possible_stack.h src/all_possible_stack.c src/help_stack.c src/help_stack.h)