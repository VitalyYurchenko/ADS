//
//  bisearch.c
//  ADS
//
//  Created by Vitaly Yurchenko on 9/1/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include <stdlib.h>

#include "bisearch.h"

// ********************************************************************************************************************************************************** //

int bisearch(void *sorted, void *target, int size, int esize, int (*compare)(const void *key1, const void *key2))
{
    int left;
    int middle;
    int right;
    
    /* Continue searching until the left and right indices cross. */
    left = 0;
    right = size - 1;
    
    while (left <= right)
    {
        middle = (left + right) / 2;
        
        switch (compare(((char *)sorted + (esize * middle)), target))
        {
            case -1:
            {
                /* Prepare to search to the right of the middle index. */
                left = middle + 1;
                break;
            }
            case 1:
            {
                /* Prepare to search to the left of the middle index. */
                right = middle - 1;
                break;
            }
            case 0:
            {
                /* Return the exact index where the data has been found. */
                return middle;
            }
            default:
                break;
        }
    }
    
    /* Return that the data was not found. */
    return -1;
}
