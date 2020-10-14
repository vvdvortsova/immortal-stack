/**
* @file         tests.c
* @brief        Tests of methods for stack
* @author       Dvortsova Varvara BSE182 HSE
*/
#include <zconf.h>
#include <wait.h>
#include "../src/all_possible_stack.h"
/**
 * Macros define custom assert function for unit testing
 * @param nameOfMethod   Describe the name Of method where assertTestINT was called
 * @param code           Actual value
 * @param expected       Expected value
 * */
#define assertTestINT( nameOfMethod,code, expected )\
    if((code) == (expected)){\
        printf("[TEST] [ %s ] [PASSED]\n",\
                nameOfMethod);\
    }else{\
        fprintf(stderr, "[TEST] [ %s ] [FAILED]\n",\
                nameOfMethod);\
        fprintf(stderr, "[TEST] expected = %d code = %d \n",expected, code);\
    }
#define  assertFailed(nameOfMethod)\
fprintf(stderr, "[TEST] [ %s ] [FAILED]\n",\
                nameOfMethod);\

#define forkChildAssert(nameOfFunction, statement)\
    pid_t ppid = fork();\
    if(ppid < 0){\
        fprintf(stderr, "Failed to create child process\n");\
        assertFailed(nameOfFunction);\
    }\
    else if(ppid == 0){\
    statement\
    }else{\
      int status = 0;\
      waitpid(ppid, &status, 0);\
      if (WIFEXITED(status)){\
        int exitCode = WEXITSTATUS(status);\
        assertTestINT(nameOfFunction, exitCode , EXIT_FAILURE);\
      }\
    }\




void stackIntConstructor(){
    STACK(Stack,int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    assertTestINT("stackIntConstructor",STACK(StackSize,int)(&stack),0);
}

void stackSizeAndPush(){
    STACK(Stack,int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush,int)(&stack, 100);
    STACK(StackPush,int)(&stack, 200);
    assertTestINT("stackSizeAndPush",STACK(StackSize,int)(&stack),2);
}
void stackIntDestructor(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackDestructor, int)(&stack);

    forkChildAssert("stackIntDestructor",STACK(StackPop, int)(&stack);)
}

void stackIntPop(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    int value = STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPop",STACK(StackSize, int)(&stack),1);
    int value2 = STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPop",STACK(StackSize, int)(&stack),0);
}
void stackIntPopBadSize(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    int value = STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPopBadSize",STACK(StackSize, int)(&stack),1);
    int value2 = STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPopBadSize",STACK(StackSize, int)(&stack),0);
    forkChildAssert("stackIntPopBadSize",int value3 = STACK(StackPop, int)(&stack););
}


int main(){
    stackIntConstructor();
    stackIntDestructor();
    stackSizeAndPush();
    stackIntPop();
    stackIntPopBadSize();
    return 0;
}