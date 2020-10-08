#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "templates.h"
#include "help_stack.h"

#ifdef  T
#define STACK_DUMP(stack)\
  fprintf(stderr, "\t=============STACK DUMP=============\n", stack->size);                                                                        \
  fprintf(stderr, "STACK[T = %s] [%p] %s(%d) \n", ERROR_TYPE(STACK(Stack,T)), (void *)stack, __FILE__, __LINE__); \
  fprintf(stderr, "size = %d\n", stack->size);                                                                       \
  fprintf(stderr, "capacity = %d\n", stack->capacity);\
  fprintf(stderr, "\t=============STACK DUMP=============\n", stack->size);                                                                        \


typedef struct STACK(Stack,T){
    ssize_t size;
    ssize_t capacity;
    T* storage;
}STACK(Stack,T);

int STACK(StackOk,T)(STACK(Stack,T)* stack);
void STACK(StackOkOrDump,T)(STACK(Stack,T)* stack);
int STACK(StackConstructor,T)(STACK(Stack,T)* stack, ssize_t capacity);
int STACK(StackDestructor,T)(STACK(Stack,T)* stack, ssize_t size, ssize_t capacity);
int STACK(StackIsEmpty,T)(STACK(Stack,T)* stack);
int STACK(StackSize,T)(STACK(Stack,T)* stack);
int STACK(StackPush,T)(STACK(Stack,T)* stack, T value);
T  STACK(StackPop,T)(STACK(Stack,T)* stack);

#endif

