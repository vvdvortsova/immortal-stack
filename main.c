#include "stdio.h"
#include "src/all_possible_stack.h"

int main() {

    STACK(Stack,int) stack;

    StackConstructor_int(&stack,100);
//    STACK(StackConstructor, int)(&stack, 100);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));
    printf("The size of capacity = %ld\n", stack.capacity);


    STACK(StackPush,int)(&stack, 100);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));
    STACK(StackPush,int)(&stack, 200);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));
    int value = STACK(StackPop,int)(&stack);
    printf("pop value1 = %ld\n",value);
    int value2 = STACK(StackPop,int)(&stack);
    printf("pop value2 = %ld\n",value2);
    int value3 = STACK(StackPop,int)(&stack);
    printf("pop value3 = %ld\n",value3);
    int value4 = STACK(StackPop,int)(&stack);
    printf("pop value4 = %ld\n",value4);

    stack.size = -2;
    int value5 = STACK(StackPop,int)(&stack);
    printf("pop value = %ld\n",value5);
    STACK(StackPush,int)(&stack, 100);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));

    return 0;
}
