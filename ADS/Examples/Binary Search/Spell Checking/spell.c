//
//  spell.c
//  ADS
//
//  Created by Vitaly Yurchenko on 9/1/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "spell.h"

#include <stdlib.h>
#include <string.h>

#include "search.h"

// ********************************************************************************************************************************************************** //

static int compare_str(const void *str1, const void *str2);

// ********************************************************************************************************************************************************** //

#pragma mark -
#pragma mark Public

int spell(char (*dictionary)[SPELL_SIZE], int size, const char *word)
{
    /* Look up the word. */
    if (bisearch(dictionary, (void *)word, size, SPELL_SIZE, compare_str) >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

#pragma mark -
#pragma mark Private

static int compare_str(const void *str1, const void *str2)
{
    int retval;
    
    if ((retval = strcmp((const char *)str1, (const char *)str2)) > 0)
    {
        return 1;
    }
    else if (retval < 0)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
