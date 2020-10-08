//
// Created by vara on 07.10.2020.
//

#include "templates.h"
#include "all_possible_stack.h"
#ifdef T
#undef T
#endif

#define T float
#include "stack.c"
#undef T

#undef T
#include "stack.c"
#define T double


#define T int
#include "stack.c"
#undef T