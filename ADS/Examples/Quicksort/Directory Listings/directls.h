//
//  directls.h
//  ADS
//
//  Created by Vitaly Yurchenko on 9/1/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_directls_h
#define ADS_directls_h

// ********************************************************************************************************************************************************** //

#include <dirent.h>

// ********************************************************************************************************************************************************** //

/* Define a structure for directory entries. */
typedef struct Directory_
{
    char name[MAXNAMLEN + 1];
} Directory;

/* Public Interface. */
int directory(const char *path, Directory **dir);

// ********************************************************************************************************************************************************** //

#endif