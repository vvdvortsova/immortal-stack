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

//#define CANARY_CHECK

#define FILE_DUMP "stack_logs.txt"
#define MAX_SIZE_OF_FILE 20000//20kb
#define CANARY_VALUE 0xDADBEEFBADull

#ifdef  T

/**
 * Macros define custom STACK_DUMP function for getting info in stderr or file stack_lib_errors.txt
 * @param[in] stack typedef struct STACK(Stack,T)
**/
#define STACK_DUMP(stack, T, errorType)\
  FILE* file = NULL;\
  file = fopen(FILE_DUMP, "a");\
  if (!file){\
    printf("failed to open file %s",FILE_DUMP);\
    exit(EXIT_FAILURE);\
  }\
  fseek(file, 0, SEEK_END);\
  int size = ftell(file);\
  fseek(file, 0, SEEK_SET);\
  if(size > MAX_SIZE_OF_FILE){\
      fclose(fopen(FILE_DUMP, "w"));\
      file = fopen(FILE_DUMP, "a");\
  }\
  fprintf(file, "DUMP START=============\n");\
  fprintf(file, "STACK[T = %s] [%p] %s(%d) \n", GET_TYPE(T), (void *)stack, __FILE__, __LINE__);\
  fprintf(file, "size = %d\n", stack->size);\
  fprintf(file, "capacity = %d\n", stack->capacity);\
  switch(errorType){\
      case 1:\
            fprintf(file, "errorType  = STACK_NULL_POINTER\n");\
            break;\
      case 2:\
            fprintf(file, "errorType  = STACK_BAD_SIZE\n");\
            break;\
      case 3:\
            fprintf(file, "errorType  = STACK_BAD_CAPACITY\n");\
            break;\
      case 4:\
            fprintf(file, "errorType  = STACK_NULL_STORAGE\n");\
            break;\
      case 5:\
            fprintf(file, "errorType  = STACK_ERRPTR_STORAGE\n");\
            break;\
      case 6:\
            fprintf(file, "errorType  = STACK_LEFT_CANARY_SONGS\n");\
            break;\
      case 7:\
            fprintf(file, "errorType  = STACK_RIGHT_CANARY_SONGS\n");\
            break;\
      case 8:\
            fprintf(file, "errorType  = STACK_ALL_CANARY_SONGS\n");\
            break;\
      case 9:\
            fprintf(file, "errorType  = STACK_BUFFER_CANARY_LEFT_SONGS\n");\
            break;\
      case 10:\
            fprintf(file, "errorType  = STACK_BUFFER_CANARY_RIGHT_SONGS\n");\
            break;\
  };\
  fprintf(file,"DUMP END=============\n");\
  fclose(file);\
  fprintf(stderr, "DUMP JUMPED!\n");\
  exit(-1);\
  \

typedef  unsigned long long canary_size;

/**
* @brief  Struct is implementing a stack
*/
typedef struct STACK(Stack,T){
#ifdef CANARY_CHECK
    canary_size canaryLeft;
#endif
    ssize_t size;
    ssize_t capacity;
    T* storage;
#ifdef CANARY_CHECK
    canary_size canaryRight;
#endif
}STACK(Stack,T);

/**
* @brief       Method verifies the stack fields
* @param[in]   stack
 */
int STACK(StackOk,T)(STACK(Stack,T)* stack){
    if(stack == NULL)
        return STACK_NULL_POINTER;
    else if(stack->storage == NULL)
        return STACK_NULL_STORAGE;
    else if(stack->storage == ERROR_PTR)
        return STACK_ERRPTR_STORAGE;
    else if(stack->size < 0 )
        return STACK_BAD_SIZE;
    else if(stack->capacity < 0 )
        return STACK_BAD_CAPACITY;

#ifdef CANARY_CHECK
    if (stack->canaryLeft != CANARY_VALUE & stack->canaryRight != CANARY_VALUE)
            return STACK_ALL_CANARY_SONGS;
    else if (stack->canaryLeft != CANARY_VALUE)
            return STACK_LEFT_CANARY_SONGS;
    else if (stack->canaryRight != CANARY_VALUE)
            return  STACK_RIGHT_CANARY_SONGS;
    else if(((char*)stack->storage - 1)[0] != '\0')
        return STACK_BUFFER_CANARY_LEFT_SONGS;
    else if(((char*)stack->storage - 1)[-1] != '\0')
        return STACK_BUFFER_CANARY_RIGHT_SONGS;

#endif
    //todo hashing
    return STACK_OK;
}

/**
* @brief       Method verifies the stack fields and calls dump
* @param[in]   stack
 */
void STACK(StackOkOrDump,T)(STACK(Stack,T)* stack) {
    int resError = STACK(StackOk, T)(stack);
    if (resError != STACK_OK) {
            STACK_DUMP(stack,T,resError);
    }
}
/**
* @brief       Method creates the stack and initializes fields of the stack
* @param[in]   stack
* @param[in]   ssize_t capacity
 */
int STACK(StackConstructor,T)(STACK(Stack,T)* s, ssize_t capacity){
    if(s == NULL){
        fprintf(stderr, "STACK is null\n");
        exit(-1);
    }
    printf("capacity = %d\n",capacity);
#ifdef CANARY_CHECK
    s->canaryLeft = CANARY_VALUE;

    void* temp = (char*)calloc(capacity * sizeof(T) + 2*sizeof(char), sizeof(char));
    *(char*)temp = '\0';//first elem
    *((char*)(&temp + 1) - 1) = '\0';//last elem
    s->storage = (T*)((char*)temp + 1);

    s->canaryRight = CANARY_VALUE;
#else
    s->storage = (T*)calloc(capacity, sizeof(T*));
#endif
    s->size = 0;
    s->capacity = capacity;
    if(!s->storage){
        fprintf(stderr, "Constructor: can't to calloc memory to storage!\n");
        exit(-1);
    }
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
#ifdef  CANARY_CHECK
    free((char*)stack->storage - 1);
#else
    free(stack->storage);
#endif
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
    //TODO: add hashing
    //resize stack
    if(stack->size == stack->capacity) {
        stack->capacity = stack->capacity * 2;
        fprintf(stderr, "Stack was resized\n");

#ifdef  CANARY_CHECK
        void *temp = realloc((char *) stack->storage - 1, stack->capacity * sizeof(T) + 2 * sizeof(char));
        *(char *) temp = '\0';//first elem
        *((char *) (&temp + 1) - 1) = '\0';//last elem
#else
        T *temp = (T *) realloc(stack->storage, stack->capacity * sizeof(T));

#endif
        if (!temp) {
            fprintf(stderr, "Can't realloc memory to resize stack buffer\n");
            exit(-1);
        } else {
#ifdef CANARY_CHECK
            stack->storage = (T *) ((char *) temp + 1);
        }
#else
            stack->storage = temp;
        }

#endif
    }
    stack->storage[stack->size++] = value;
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
    fprintf(stderr, "Pop: size < 0\n");
    exit(-1);
}

#endif