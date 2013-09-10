//
//  search.h
//  ADS
//
//  Created by Vitaly Yurchenko on 09.09.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_search_h
#define ADS_search_h

// ********************************************************************************************************************************************************** //

/* Public Interface. */

/*
 Description:   Uses binary search to locate target in sorted, a sorted array of elements. The number of elements in sorted is specified by size.
                The size of each element is specified by esize. The function pointer compare specifies a user-defined function to compare elements.
                This function should return 1 if key1 > key2, 0 if key1 = key2, and –1 if key1 < key2.
 
 Return Value:  Index of the target if found, or –1 otherwise.
 
 Complexity:    O(lg n), where n is the number of elements to be searched.
 */
int bisearch(void *sorted, void *target, int size, int esize, int (*compare)(const void *key1, const void *key2));

// ********************************************************************************************************************************************************** //

#endif
