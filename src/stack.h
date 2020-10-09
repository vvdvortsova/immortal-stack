/**
* @file         stack.h
* @brief        Headers of methods for stack
* @author       Dvortsova Varvara BSE182 HSE
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "templates.h"
#include "stack_errors.h"

#ifdef  T
/**
 * Macros define custom STACK_DUMP function for getting info in stderr or file stack_lib_errors.txt
 * @param[in] stack typedef struct STACK(Stack,T)
**/
#define STACK_DUMP(stack)\
  fprintf(stderr, "\t=============STACK DUMP=============\n");                                                                        \
  fprintf(stderr, "STACK[T = %s] [%p] %s(%d) \n", ERROR_TYPE(STACK(Stack,T)), (void *)stack, __FILE__, __LINE__); \
  fprintf(stderr, "size = %d\n", stack->size);                                                                       \
  fprintf(stderr, "capacity = %d\n", stack->capacity);\
  fprintf(stderr, "\t=============STACK DUMP=============\n");     \
  FILE* file = NULL;\
  char* fileName = "stack_lib_logs.txt";\
  file = fopen(fileName, "w");\
  if (!file) {\
  printf("failed to open file %s",fileName);\
  exit(EXIT_FAILURE);}\
  fprintf(file, "\t=============STACK DUMP=============\n");\
  fprintf(file, "STACK[T = %s] [%p] %s(%d) \n", ERROR_TYPE(STACK(Stack,T)), (void *)stack, __FILE__, __LINE__);\
  fprintf(file, "size = %d\n", stack->size);\
  fprintf(file, "capacity = %d\n", stack->capacity);\
  fprintf(file, "\t=============STACK DUMP=============\n");\
  fclose(file);\
  \

/**
* @brief  Struct is implementing a stack
*/
typedef struct STACK(Stack,T){
    ssize_t size;
    ssize_t capacity;
    T* storage;
}STACK(Stack,T);

/**
* @brief       Stack Dump
 */
int STACK(StackDump,T)(STACK(Stack,T)* stack);
/**
* @brief       Method verifies the stack fields
* @param[in]   stack
 */
int STACK(StackOk,T)(STACK(Stack,T)* stack);

/**
* @brief       Method verifies the stack fields and calls dump
* @param[in]   stack
 */
void STACK(StackOkOrDump,T)(STACK(Stack,T)* stack);

/**
* @brief       Method creates the stack and initializes fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
 */
int STACK(StackConstructor,T)(STACK(Stack,T)* stack, ssize_t capacity);

/**
* @brief       Method destroys the stack and "breaks down" all fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
* @param[in]   ssize_t size
 */
int STACK(StackDestructor,T)(STACK(Stack,T)* stack, ssize_t size, ssize_t capacity);

/**
* @brief       Method checks the size of the stack
* @param[in]   stack
 */
int STACK(StackIsEmpty,T)(STACK(Stack,T)* stack);

/**
* @brief       Method return the size of the stack
* @param[in]   stack
 */
int STACK(StackSize,T)(STACK(Stack,T)* stack);

/**
* @brief       Method pushes the value of T type to the top of the stack
* @param[in]   stack
* @param[in]   T value
 */
int STACK(StackPush,T)(STACK(Stack,T)* stack, T value);
/**
* @brief       Method gets the value of T type from the top of the stack
* @param[in]   stack
* return   T value
 */
T  STACK(StackPop,T)(STACK(Stack,T)* stack);

#endif

