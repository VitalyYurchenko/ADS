//
//  bistree.h
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_bistree_h
#define ADS_bistree_h

// ********************************************************************************************************************************************************** //

#include "bitree.h"

// ********************************************************************************************************************************************************** //

/* Define balance factors for AVL trees. */
#define AVL_LFT_HEAVY   1
#define AVL_BALANCED    0
#define AVL_RGT_HEAVY  -1

/* Define a structure for nodes in AVL trees. */
typedef struct AVLNode_
{
    void *data;
    int hidden;
    int factor;
} AVLNode;

/* Implement binary search trees as binary trees. */
typedef BiTree BisTree;

/* Public Interface. */
void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data));
void bistree_destroy(BisTree *tree);
int bistree_insert(BisTree *tree, const void *data);
int bistree_remove(BisTree *tree, const void *data);
int bistree_lookup(BisTree *tree, void **data);
#define bistree_size(tree) ((tree)->size)

// ********************************************************************************************************************************************************** //

#endif
