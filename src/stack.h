/**
* @file         stack.h
* @brief        Headers of methods for stack
* @author       Dvortsova Varvara BSE182 HSE
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
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

#define MY_FILE_NAME "stack_lib_logs"
#define SAMPLE_DATA  "Content Content"
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
int STACK(StackDump,T)(STACK(Stack,T)* stack){
//    FILE* fileToWriteResult = NULL;
//    char* nameOfFile = "stack_lib_logs.txt";
//    printf("awadawdawdawd\n");
//
//    fileToWriteResult = fopen(nameOfFile, "w");
//    if (!fileToWriteResult){
//        printf("failed to open file");
//        exit(EXIT_FAILURE);
//    }
//    fwrite ("aaaaa",1,1,fileToWriteResult);
//    fclose(fileToWriteResult);

    char file_data[256];
    int file_size = sizeof(file_data);

    // fill in some sample data
    memcpy(file_data, SAMPLE_DATA, sizeof(SAMPLE_DATA));

    FILE *file = fopen(MY_FILE_NAME, "w+");
    if (file) {
        fwrite(file_data, 1, file_size, file);
        fclose(file);}
}

/**
* @brief       Method verifies the stack fields
* @param[in]   stack
 */
int STACK(StackOk,T)(STACK(Stack,T)* stack){
    {
    if(stack == NULL)
        return STACK_NULL_POINTER;
    else if(stack->storage == NULL)
        return STACK_NULL_STORAGE;
    else if (stack->storage == perror)
        return STACK_ERRPTR_STORAGE;
    else if(stack->size < 0 )
        return STACK_BAD_SIZE;
    else if(stack->capacity < 0 )
        return STACK_BAD_CAPACITY;
    return STACK_OK;
}
}


/**
* @brief       Method verifies the stack fields and calls dump
* @param[in]   stack
 */
void STACK(StackOkOrDump,T)(STACK(Stack,T)* stack) {
    int resError = STACK(StackOk, T)(stack);
    //TODO:
    if (resError != STACK_OK) {
//        STACK_DUMP(stack)
        STACK(StackDump,T)(stack);
    }
}
/**
* @brief       Method creates the stack and initializes fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
 */
int STACK(StackConstructor,T)(STACK(Stack,T)* s, ssize_t capacity){
    if(s == NULL) {
        fprintf(stderr, "Insufficient memory to initialize stack.\n");
        return STACK_NULL_POINTER;
    }
    printf("capacity = %d\n",capacity);
    s->size = 0;
    s->capacity = capacity;
    s->storage = calloc(capacity,sizeof(T));
    if(!s->storage)
        return STACK_BAD_CALLOC;
    return STACK_OK;
}

/**
* @brief       Method destroys the stack and "breaks down" all fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
* @param[in]   ssize_t size
 */
int STACK(StackDestructor,T)(STACK(Stack,T)* stack, ssize_t size, ssize_t capacity){
    STACK(StackOkOrDump, T)(stack);
    if(!stack || !stack->storage)
        return STACK_NULL_POINTER;
    stack->size = -1;
    stack->capacity = -1;
    free(stack->storage);
    stack->storage = ERROR_PTR;
    return STACK_OK;
}
/**
* @brief       Method checks the size of the stack
* @param[in]   stack
 */
int STACK(StackIsEmpty,T)(STACK(Stack,T)* stack){
    return (stack->size <= 0);
}
/**
* @brief       Method return the size of the stack
* @param[in]   stack
 */
int STACK(StackSize,T)(STACK(Stack,T)* stack){
    STACK(StackOkOrDump, T)(stack);
    return stack->size;
}

/**
* @brief       Method pushes the value of T type to the top of the stack
* @param[in]   stack
* @param[in]   T value
 */
int STACK(StackPush,T)(STACK(Stack,T)* stack, T value){
    STACK(StackOkOrDump, T)(stack);

    if(stack->size == stack->capacity) {
        fprintf(stderr, "Element can not be pushed: Stack is full.\n");
        return STACK_FULL;
    }
    if(!value)
        exit(-1);

    stack->size++;
    stack->storage[stack->size - 1] = value;

    STACK(StackOkOrDump, T)(stack);
    return STACK_OK;
}
/**
* @brief       Method gets the value of T type from the top of the stack
* @param[in]   stack
* return   T value
 */
T  STACK(StackPop,T)(STACK(Stack,T)* stack){
    STACK(StackOkOrDump, T)(stack);
    if(stack->size > 0){
        T elem = stack->storage[stack->size - 1];
        stack->size--;
        return elem;
    }
    //TODO: what should I do here?
//    exit();
}

#endif