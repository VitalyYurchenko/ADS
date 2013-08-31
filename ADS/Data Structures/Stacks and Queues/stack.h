//
//  stack.h
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_stack_h
#define ADS_stack_h

// ********************************************************************************************************************************************************** //

#include "list.h"

// ********************************************************************************************************************************************************** //

/* Implement stacks as linked lists. */
typedef List Stack;

/* Public Interface. */
#define stack_init list_init
#define stack_destroy list_destroy
int stack_push(Stack *stack, const void *data);
int stack_pop(Stack *stack, void **data);
#define stack_peek(stack) ((stack)->head == NULL ? NULL : (stack)->head->data)
#define stack_size list_size

// ********************************************************************************************************************************************************** //

#endif
