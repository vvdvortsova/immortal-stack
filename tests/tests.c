/**
* @file         tests.c
* @brief        Tests of methods for stack
* @author       Dvortsova Varvara BSE182 HSE
*/
#include "../src/all_possible_stack.h"

void stackIntConstructor(){
    STACK(Stack,int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    assert(STACK(StackSize,int)(&stack) == 0);
}

void stackSizeAndPush(){
    STACK(Stack,int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush,int)(&stack, 100);
    STACK(StackPush,int)(&stack, 200);
    assert(STACK(StackSize,int)(&stack) == 2);
}
void stackIntDestructor(){

}

void stackIntPop(){
    STACK(Stack,int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush,int)(&stack, 100);
    STACK(StackPush,int)(&stack, 200);
    T value = STACK(StackPop,int)(&stack);
    assert(STACK(StackSize,int)(&stack) == 1);
    T value2 = STACK(StackPop,int)(&stack);
    assert(STACK(StackSize,int)(&stack) == 0);
}
int main(){
    stackIntConstructor();
    stackIntDestructor();
    stackSizeAndPush();
    stackIntPop();
    return 0;
}