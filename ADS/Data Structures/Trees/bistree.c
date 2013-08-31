//
//  bistree.c
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "bistree.h"

#include <stdlib.h>
#include <string.h>

// ********************************************************************************************************************************************************** //

static void rotate_left(BiTreeNode **node);
static void rotate_right(BiTreeNode **node);
static void destroy_left(BisTree *tree, BiTreeNode *node);
static void destroy_right(BisTree *tree, BiTreeNode *node);
static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced);
static int hide(BisTree *tree, BiTreeNode *node, const void *data);
static int lookup(BisTree *tree, BiTreeNode *node, void **data);

// ********************************************************************************************************************************************************** //

#pragma mark -
#pragma mark Public

void bistree_init(BisTree *tree, int (*compare)(const void *key1, const void *key2), void (*destroy)(void *data))
{
    /* Initialize the tree. */
    bitree_init(tree, destroy);
    tree->compare = compare;
    
    return;
}

void bistree_destroy(BisTree *tree)
{
    /* Destroy all nodes in the tree. */
    destroy_left(tree, NULL);
    
    /* No operations are allowed now, but clear the structure as a precaution. */
    memset(tree, 0, sizeof(BisTree));
    
    return;
}

int bistree_insert(BisTree *tree, const void *data)
{
    int balanced = 0;
    
    return insert(tree, &bitree_root(tree), data, &balanced);
}

int bistree_remove(BisTree *tree, const void *data)
{
    return hide(tree, bitree_root(tree), data);
}

int bistree_lookup(BisTree *tree, void **data)
{
    return lookup(tree, bitree_root(tree), data);
}

#pragma mark -
#pragma mark Private

static void rotate_left(BiTreeNode **node)
{
    BiTreeNode *left;
    BiTreeNode *grandchild;
    
    left = bitree_left(*node);
    
    if (((AVLNode *)bitree_data(left))->factor == AVL_LFT_HEAVY)
    {
        /* Perform an LL rotation. */
        bitree_left(*node) = bitree_right(left);
        bitree_right(left) = *node;
        ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AVLNode *)bitree_data(left))->factor = AVL_BALANCED;
        *node = left;
    }
    else
    {
        /* Perform an LR rotation. */
        grandchild = bitree_right(left);
        bitree_right(left) = bitree_left(grandchild);
        bitree_left(grandchild) = left;
        bitree_left(*node) = bitree_right(grandchild);
        bitree_right(grandchild) = *node;
        
        switch (((AVLNode *)bitree_data(grandchild))->factor)
        {
            case AVL_LFT_HEAVY:
            {
                ((AVLNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
                ((AVLNode *)bitree_data(left))->factor = AVL_BALANCED;
                
                break;
            }
            case AVL_BALANCED:
            {
                ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AVLNode *)bitree_data(left))->factor = AVL_BALANCED;
                
                break;
            }
            case AVL_RGT_HEAVY:
            {
                ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AVLNode *)bitree_data(left))->factor = AVL_LFT_HEAVY;
                
                break;
            }
            default:
                break;
        }
        
        ((AVLNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
    
    return;
}

static void rotate_right(BiTreeNode **node)
{
    BiTreeNode *right;
    BiTreeNode *grandchild;
    
    right = bitree_right(*node);
    
    if (((AVLNode *)bitree_data(right))->factor == AVL_RGT_HEAVY)
    {
        /* Perform an RR rotation. */
        bitree_right(*node) = bitree_left(right);
        bitree_left(right) = *node;
        ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
        ((AVLNode *)bitree_data(right))->factor = AVL_BALANCED;
        *node = right;
    }
    else
    {
        /* Perform an RR rotation. */
        grandchild = bitree_left(right);
        bitree_left(right) = bitree_right(grandchild);
        bitree_right(grandchild) = right;
        bitree_right(*node) = bitree_left(grandchild);
        bitree_left(grandchild) = *node;
        
        switch (((AVLNode *)bitree_data(grandchild))->factor)
        {
            case AVL_LFT_HEAVY:
            {
                ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AVLNode *)bitree_data(right))->factor = AVL_RGT_HEAVY;
                
                break;
            }
            case AVL_BALANCED:
            {
                ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
                ((AVLNode *)bitree_data(right))->factor = AVL_BALANCED;
                
                break;
            }
            case AVL_RGT_HEAVY:
            {
                ((AVLNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
                ((AVLNode *)bitree_data(right))->factor = AVL_BALANCED;
                
                break;
            }
            default:
                break;
        }
        
        ((AVLNode *)bitree_data(grandchild))->factor = AVL_BALANCED;
        *node = grandchild;
    }
    
    return;
}

static void destroy_left(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    
    /* Do not allow destruction of an empty tree. */
    if (bitree_size(tree) == 0)
    {
        return;
    }
    
    /* Determine where to destroy nodes. */
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->left;
    }
    
    /* Destroy the nodes. */
    if (*position != NULL)
    {
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        
        if (tree->destroy != NULL)
        {
            /* Call a user-defined function to free dynamically allocated data. */
            tree->destroy(((AVLNode *)(*position)->data)->data);
        }
        
        /* Free the AVL data in the node, then free the node itself. */
        free((*position)->data);
        free(*position);
        *position = NULL;
        
        /* Adjust the size of the tree to account for the destroyed node. */
        tree->size--;
    }
    
    return;
}

static void destroy_right(BisTree *tree, BiTreeNode *node)
{
    BiTreeNode **position;
    
    /* Do not allow destruction of an empty tree. */
    if (bitree_size(tree) == 0)
    {
        return;
    }
    
    /* Determine where to destroy nodes. */
    if (node == NULL)
    {
        position = &tree->root;
    }
    else
    {
        position = &node->right;
    }
    
    /* Destroy the nodes. */
    if (*position != NULL)
    {
        destroy_left(tree, *position);
        destroy_right(tree, *position);
        
        if (tree->destroy != NULL)
        {
            /* Call a user-defined function to free dynamically allocated data. */
            tree->destroy(((AVLNode *)(*position)->data)->data);
        }
        
        /* Free the AVL data in the node, then free the node itself. */
        free((*position)->data);
        free(*position);
        *position = NULL;
        
        /* Adjust the size of the tree to account for the destroyed node. */
        tree->size--;
    }
    
    return;
}

static int insert(BisTree *tree, BiTreeNode **node, const void *data, int *balanced)
{
    AVLNode *avl_data;
    int cmpval;
    int retval;
    
    /* Insert the data into the tree. */
    if (bitree_is_eob(*node))
    {
        /* Handle insertion into an empty tree. */
        if ((avl_data = (AVLNode *)malloc(sizeof(AVLNode))) == NULL)
        {
            return -1;
        }
        
        avl_data->factor = AVL_BALANCED;
        avl_data->hidden = 0;
        avl_data->data = (void *)data;
        
        return bitree_insert_left(tree, *node, avl_data);
    }
    else
    {
        /* Handle insertion into a tree that is not empty. */
        cmpval = tree->compare(data, ((AVLNode *)bitree_data(*node))->data);
        
        if (cmpval < 0)
        {
            /* Move to the left. */
            if (bitree_is_eob(bitree_left(*node)))
            {
                if ((avl_data = (AVLNode *)malloc(sizeof(AVLNode))) == NULL)
                {
                    return -1;
                }
                
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;
                
                if (bitree_insert_left(tree, *node, avl_data) != 0)
                {
                    return -1;
                }
                
                *balanced = 0;
            }
            else
            {
                if ((retval = insert(tree, &bitree_left(*node), data, balanced)) != 0)
                {
                    return retval;
                }
            }
            
            /* Ensure that the tree remains balanced. */
            if (!(*balanced))
            {
                switch (((AVLNode *)bitree_data(*node))->factor)
                {
                    case AVL_LFT_HEAVY:
                    {
                        rotate_left(node); *balanced = 1;
                        break;
                    }
                    case AVL_BALANCED:
                    {
                        ((AVLNode *)bitree_data(*node))->factor = AVL_LFT_HEAVY;
                        break;
                    }
                    case AVL_RGT_HEAVY:
                    {
                        ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                    }
                    default:
                        break;
                }
            }
        } /* if (cmpval < 0) */
        else if (cmpval > 0)
        {
            /* Move to the right. */
            if (bitree_is_eob(bitree_right(*node)))
            {
                if ((avl_data = (AVLNode *)malloc(sizeof(AVLNode))) == NULL)
                {
                    return -1;
                }
                
                avl_data->factor = AVL_BALANCED;
                avl_data->hidden = 0;
                avl_data->data = (void *)data;
                
                if (bitree_insert_right(tree, *node, avl_data) != 0)
                {
                    return -1;
                }
                
                *balanced = 0;
            }
            else
            {
                if ((retval = insert(tree, &bitree_right(*node), data, balanced)) != 0)
                {
                    return retval;
                }
            }
            
            /* Ensure that the tree remains balanced. */
            if (!(*balanced))
            {
                switch (((AVLNode *)bitree_data(*node))->factor)
                {
                    case AVL_LFT_HEAVY:
                    {
                        ((AVLNode *)bitree_data(*node))->factor = AVL_BALANCED;
                        *balanced = 1;
                        break;
                    }
                    case AVL_BALANCED:
                    {
                        ((AVLNode *)bitree_data(*node))->factor = AVL_RGT_HEAVY;
                        break;
                    }
                    case AVL_RGT_HEAVY:
                    {
                        rotate_right(node);
                        *balanced = 1;
                        break;
                    }
                    default:
                        break;
                }
            }
        } /* if (cmpval > 0) */
        else
        {
            /* Handle finding a copy of the data. */
            if (!((AVLNode *)bitree_data(*node))->hidden)
            {
                /* Do nothing since the data is in the tree and not hidden. */
                return 1;
            }
            else
            {
                /* Insert the new data and mark it as not hidden. */
                if (tree->destroy != NULL)
                {
                    /* Destroy the hidden data since it is being replaced. */
                    tree->destroy(((AVLNode *)bitree_data(*node))->data);
                }
                
                ((AVLNode *)bitree_data(*node))->data = (void *)data;
                ((AVLNode *)bitree_data(*node))->hidden = 0;
                
                /* Do not rebalance because the tree structure is unchanged. */
                *balanced = 1;
            }
        }
    }
    
    return 0;
}

static int hide(BisTree *tree, BiTreeNode *node, const void *data)
{
    int cmpval;
    int retval;
    
    if (bitree_is_eob(node))
    {
        /* Return that the data was not found. */
        return -1;
    }
    
    cmpval = tree->compare(data, ((AVLNode *)bitree_data(node))->data);
    
    if (cmpval < 0)
    {
        /* Move to the left. */
        retval = hide(tree, bitree_left(node), data);
    }
    else if (cmpval > 0)
    {
        /* Move to the right. */
        retval = hide(tree, bitree_right(node), data);
    }
    else
    {
        /* Mark the node as hidden. */
        ((AVLNode *)bitree_data(node))->hidden = 1;
        retval = 0;
    }
    
    return retval;
}

static int lookup(BisTree *tree, BiTreeNode *node, void **data)
{
    int cmpval;
    int retval;
    
    if (bitree_is_eob(node))
    {
        /* Return that the data was not found. */
        return -1;
    }
    
    cmpval = tree->compare(*data, ((AVLNode *)bitree_data(node))->data);
    
    if (cmpval < 0)
    {
        /* Move to the left. */
        retval = lookup(tree, bitree_left(node), data);
    }
    else if (cmpval > 0)
    {
        /* Move to the right. */
        retval = lookup(tree, bitree_right(node), data);
    }
    else
    {
        if (!((AVLNode *)bitree_data(node))->hidden)
        {
            /* Pass back the data from the tree. */
            *data = ((AVLNode *)bitree_data(node))->data;
            retval = 0;
        }
        else
        {
            /* Return that the data was not found. */
            return -1;
        }
    }
    
    return retval;
}
