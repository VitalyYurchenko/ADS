//
//  fibonacci.c
//  ADS
//
//  Created by Vitaly Yurchenko on 9/15/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "fibonacci.h"

#include <stdlib.h>

// ********************************************************************************************************************************************************** //

unsigned long long fibonacci(const int n)
{
    unsigned long long retval = 0;
    unsigned long long val1 = 1;
    unsigned long long val2;
    int i;
    
    for (i = 1; i <= n; i++)
    {
        val2 = retval;
        retval += val1;
        val1 = val2;
    }
    
    return retval;
}
