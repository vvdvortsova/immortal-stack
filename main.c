#include "stdio.h"
#include "src/all_possible_stack.h"


int main() {

    STACK(Stack,int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));
    printf("The size of capacity = %ld\n", stack.capacity);


    STACK(StackPush,int)(&stack, 100);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));
    STACK(StackPush,int)(&stack, 200);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));
    T value = STACK(StackPop,int)(&stack);
    printf("pop value = %ld\n",value);
    T value2 = STACK(StackPop,int)(&stack);
    printf("pop value = %ld\n",value2);

    stack.size = -1;
    STACK(StackPush,int)(&stack, 100);
    printf("The size of stack = %d\n", STACK(StackSize,int)(&stack));

    return 0;
}
