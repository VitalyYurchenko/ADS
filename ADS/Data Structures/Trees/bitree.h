//
//  bitree.h
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_bitree_h
#define ADS_bitree_h

// ********************************************************************************************************************************************************** //

/* Define a structure for binary tree nodes. */
typedef struct BiTreeNode_
{
    void *data;
    struct BiTreeNode_ *left;
    struct BiTreeNode_ *right;
} BiTreeNode;

/* Define a structure for binary trees. */
typedef struct BiTree_
{
    int size;
    int (*compare)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    BiTreeNode *root;
} BiTree;

/* Public Interface. */
void bitree_init(BiTree *tree, void (*destroy)(void *data));
void bitree_destroy(BiTree *tree);
int bitree_insert_left(BiTree *tree, BiTreeNode *node, const void *data);
int bitree_insert_right(BiTree *tree, BiTreeNode *node, const void *data);
void bitree_remove_left(BiTree *tree, BiTreeNode *node);
void bitree_remove_right(BiTree *tree, BiTreeNode *node);
int bitree_merge(BiTree *merge, BiTree *left, BiTree *right, const void *data);
#define bitree_size(tree) ((tree)->size)
#define bitree_root(tree) ((tree)->root)
#define bitree_is_eob(node) ((node) == NULL)
#define bitree_is_leaf(node) ((node)->left == NULL && (node)->right == NULL)
#define bitree_data(node) ((node)->data)
#define bitree_left(node) ((node)->left)
#define bitree_right(node) ((node)->right)

// ********************************************************************************************************************************************************** //

#endif
