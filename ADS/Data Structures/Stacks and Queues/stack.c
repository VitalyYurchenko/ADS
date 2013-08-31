//
//  stack.c
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "stack.h"

#include <stdlib.h>

// ********************************************************************************************************************************************************** //

int stack_push(Stack *stack, const void *data)
{
    /* Push the data onto the stack. */
    return list_insert_next(stack, NULL, data);
}

int stack_pop(Stack *stack, void **data)
{
    /* Pop the data off the stack. */
    return list_remove_next(stack, NULL, data);
}