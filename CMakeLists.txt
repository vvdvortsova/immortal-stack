cmake_minimum_required(VERSION 3.15)
project(immortal_stack C)
add_compile_options( -Wall -Wextra -Wfloat-equal)

set(CMAKE_C_STANDARD 11)

add_executable(immortal_stack
        main.c
        src/stack.h
        src/templates.h
        src/all_possible_stack.h
        src/stack_errors.c
        src/stack_errors.h)

add_executable(test
        tests/tests.c
        src/stack.h
        src/templates.h
        src/all_possible_stack.h
        src/stack_errors.c
        src/stack_errors.h)
set(RESOURCE_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/src/stack_lib_logs.txt)