//
//  directls.c
//  ADS
//
//  Created by Vitaly Yurchenko on 9/1/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "directls.h"

#include <stdlib.h>
#include <string.h>

#include "qksort.h"

// ********************************************************************************************************************************************************** //

static int compare_dir(const void *key1, const void *key2);

// ********************************************************************************************************************************************************** //

#pragma mark -
#pragma mark Public

int directory(const char *path, Directory **dir)
{
    DIR *dirptr;
    Directory *temp;
    struct dirent *curdir;
    int count;
    int i;
    
    /* Open the directory. */
    if ((dirptr = opendir(path)) == NULL)
    {
        return -1;
    }
    
    /* Get the directory entries. */
    *dir = NULL;
    count = 0;
    
    while ((curdir = readdir(dirptr)) != NULL)
    {
        count++;
        
        if ((temp = (Directory *)realloc(*dir, count * sizeof(Directory))) == NULL)
        {
            free(*dir);
            
            return -1;
        }
        else
        {
            *dir = temp;
        }
        
        strcpy(((*dir)[count - 1]).name, curdir->d_name);
    }
    
    closedir(dirptr);
    
    /* Sort the directory entries by name. */
    if (qksort(*dir, count, sizeof(Directory), 0, count - 1, compare_dir) != 0)
    {
        return -1;
    }
    
    /* Return the number of directory entries. */
    return count;
}

#pragma mark -
#pragma mark Private

static int compare_dir(const void *key1, const void *key2)
{
    int retval;
    
    if ((retval = strcmp(((const Directory *)key1)->name, ((const Directory *)key2)->name)) > 0)
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
