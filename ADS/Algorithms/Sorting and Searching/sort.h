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
 Description:   Uses counting sort to sort the array of integers in data. The number of integers in data is specified by size.
                The argument k specifies the maximum integer in data, plus 1. When ctsort returns, data contains the sorted integers.
 
 Return Value:  0 if sorting is successful, or –1 otherwise.
 
 Complexity:    O(n + k), where n is the number of integers to be sorted and k is the maximum integer in the unsorted set, plus 1.
 */
int ctsort(int *data, int size, int k);

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
 Return Value:  0 if sorting is successful, or –1 otherwise.
 
 Description:   Uses merge sort to sort the array of elements in data. The number of elements in data is specified by size.
                The size of each element is specified by esize. The arguments i and k define the current division being sorted
                and initially should be 0 and size – 1, respectively. The function pointer compare specifies a user-defined function to compare elements.
                It should perform in a manner similar to that described for issort. When mgsort returns, data contains the sorted elements.
 
 Complexity:    O(n lg n), where n is the number of elements to be sorted.
 */
int mgsort(void *data, int size, int esize, int i, int k, int (*compare)(const void *key1, const void *key2));

/*
 Description:   Uses quicksort to sort the array of elements in data. The number of elements in data is specified by size.
                The size of each element is specified by esize. The arguments i and k define the current partition being sorted
                and initially should be 0 and size – 1, respectively. The function pointer compare specifies a user-defined function to compare elements.
                It should perform in a manner similar to that described for issort. When qksort returns, data contains the sorted elements.
 
 Return Value:  0 if sorting is successful, or –1 otherwise.
 
 Complexity:    O(n lg n), where n is the number of elements to be sorted.
 */
int qksort(void *data, int size, int esize, int i, int k, int (*compare)(const void *key1, const void *key2));

/*
 Description:   Uses radix sort to sort the array of integers in data. The number of integers in data is specified by size.
                The argument p specifies the number of digit positions in each integer. The argument k specifies the radix.
                When rxsort returns, data contains the sorted integers.
 
 Return Value:  0 if sorting is successful, or –1 otherwise.
 
 Complexity:    O(pn + pk), where n is the number of integers to be sorted, k is the radix, and p is the number of digit positions.
 */
int rxsort(int *data, int size, int p, int k);

// ********************************************************************************************************************************************************** //

#endif
