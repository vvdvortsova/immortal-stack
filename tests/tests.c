/**
* @file         tests.c
* @brief        Tests of methods for stack
* @author       Dvortsova Varvara BSE182 HSE
* @include      zconf.h, wait.h, ../src/all_possible_stack.h
*/
#include <zconf.h>
#include <wait.h>
#include "../src/all_possible_stack.h"
/**
 * Macros defines a custom assert function for unit testing
 * @param nameOfMethod   Describe the name Of method where assertTestINT was called
 * @param code           Actual value
 * @param expected       Expected value
 * */
#define assertTestINT( nameOfMethod, code, expected )\
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

/**
 * Macros defines a custom assert function for checking exit code from child process
 * @param nameOfMethod   Describe the name Of method where forkChildAssert was called
 * @param statement      Statement runs in child process
 * */
#define forkChildAssert(nameOfFunction, statement, expectedCode)\
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
        assertTestINT(nameOfFunction, exitCode , expectedCode);\
      }\
    }\


void stackIntConstructor(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    assertTestINT("stackIntConstructor",STACK(StackSize, int)(&stack),0);
}

void stackSizeAndPush(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    assertTestINT("stackSizeAndPush",STACK(StackSize, int)(&stack),2);
}
void stackIntDestructor(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackDestructor, int)(&stack);


    forkChildAssert("stackIntDestructor",STACK(StackPop, int)(&stack);, EXIT_FAILURE)
}

void stackIntPop(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPop",STACK(StackSize, int)(&stack),1);
    STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPop",STACK(StackSize, int)(&stack),0);
}

void stackIntPushResizeMany(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 3);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackPush, int)(&stack, 200);
    forkChildAssert("stackIntPushResizeMany",    STACK(StackPush, int)(&stack, 200);, 0)
}

void stackIntPopBadSize(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPopBadSize",STACK(StackSize, int)(&stack),1);
    STACK(StackPop, int)(&stack);
    assertTestINT("stackIntPopBadSize",STACK(StackSize, int)(&stack),0);
    forkChildAssert("stackIntPopBadSize",STACK(StackPop, int)(&stack);, EXIT_FAILURE);
}

void shootAtTheLeftCanary(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackPop, int)(&stack);
    STACK(StackPop, int)(&stack);
#ifdef CANARY_CHECK
    //shoot
    stack.canaryLeft = 42;
    forkChildAssert("shootAtTheLeftCanary",STACK(StackPush, int)(&stack, 100);, EXIT_FAILURE);
#endif
}
void shootAtTheRightCanary(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackPop, int)(&stack);
    STACK(StackPop, int)(&stack);
    //shoot
#ifdef CANARY_CHECK
    stack.canaryRight = 42;
    forkChildAssert("shootAtTheRightCanary",STACK(StackPush, int)(&stack, 100);, EXIT_FAILURE);
#endif
}

void shootAtTheBothCanary(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 200);
    STACK(StackPop, int)(&stack);
    STACK(StackPop, int)(&stack);
    //shoot
#ifdef CANARY_CHECK
    stack.canaryLeft = 42;
    stack.canaryRight = 42;
    forkChildAssert("shootAtTheBothCanary",STACK(StackPush, int)(&stack, 100);, EXIT_FAILURE);
#endif
}

void stackIntHashCheck(){
    STACK(Stack, int) stack;
    STACK(StackConstructor, int)(&stack, 100);
    STACK(StackPush, int)(&stack, 100);
    //shoot
#ifdef HASH_CHECK
    stack.canaryHash = 80;
    forkChildAssert("stackIntHashCheck",STACK(StackPush, int)(&stack, 100);, EXIT_FAILURE);
#endif
}

int main(){
    stackIntConstructor();
    stackIntDestructor();
    stackSizeAndPush();
    stackIntPop();
    stackIntPopBadSize();
    shootAtTheLeftCanary();
    shootAtTheRightCanary();
    shootAtTheBothCanary();
    stackIntHashCheck();
    stackIntPushResizeMany();
    return 0;
}