//
//  sort.h
//  ADS
//
//  Created by Vitaly Yurchenko on 09.09.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_sort_h
#define ADS_sort_h

// ********************************************************************************************************************************************************** //

/* Public Interface. */

/*
 Return Value:  0 if sorting is successful, or –1 otherwise.
 
 Description:   Uses insertion sort to sort the array of elements in data. The number of elements in data is specified by size.
                The size of each element is specified by esize. The function pointer compare specifies a user-defined function to compare elements.
                This function should return 1 if key1 > key2, 0 if key1 = key2, and –1 if key1 < key2 for an ascending sort.
                For a descending sort, compare should reverse the cases returning 1 and –1. When issort returns, data contains the sorted elements.
 
 Complexity:    O(n2), where n is the number of elements to be sorted.
 */
int issort(void *data, int size, int esize, int (*compare)(const void *key1, const void *key2));

/*
 Description:   Uses quicksort to sort the array of elements in data. The number of elements in data is specified by size.
                The size of each element is specified by esize. The arguments i and k define the current partition being sorted
                and initially should be 0 and size – 1, respectively. The function pointer compare specifies a user-defined function to compare elements.
                It should perform in a manner similar to that described for issort. When qksort returns, data contains the sorted elements.
 
 Return Value:  0 if sorting is successful, or –1 otherwise.
 
 Complexity:    O(n lg n), where n is the number of elements to be sorted.
 */
int qksort(void *data, int size, int esize, int i, int k, int (*compare)(const void *key1, const void *key2));

// ********************************************************************************************************************************************************** //

#endif
