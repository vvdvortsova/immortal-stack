#ifdef T

int STACK(StackDump,T)(STACK(Stack,T)* stack){
    FILE* fileToWriteResult = NULL;
    char* nameOfFile = "stack_lib_logs.txt";
    printf("awadawdawdawd\n");
    fileToWriteResult = fopen(nameOfFile, "w");
    if (!fileToWriteResult){
        printf("failed to open file");
        exit(EXIT_FAILURE);
    }
    fprintf(fileToWriteResult,"%s\n", "aaaaa");
    fclose(fileToWriteResult);
}

int STACK(StackOk, T)(STACK(Stack,T)* stack){
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
 void STACK(StackOkOrDump, T)(STACK(Stack,T)* stack){
    int resError = STACK(StackOk, T)(stack);
    //TODO:
    if(resError != STACK_OK){
        STACK_DUMP(stack)
//        STACK(StackDump,T)(stack);
    }
}

int STACK(StackConstructor,T)(STACK(Stack,T)* s, ssize_t capacity){
    //create an empty stack
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

int STACK(StackIsEmpty,T)(STACK(Stack,T)* stack){
    return (stack->size <= 0);
}

int STACK(StackSize,T)(STACK(Stack,T)* stack){
    STACK(StackOkOrDump, T)(stack);
    return stack->size;
}

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
