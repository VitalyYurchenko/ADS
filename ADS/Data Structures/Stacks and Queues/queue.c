//
//  queue.c
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "queue.h"

#include <stdlib.h>

// ********************************************************************************************************************************************************** //

int queue_enqueue(Queue *queue, const void *data)
{
    /* Enqueue the data. */
    return list_insert_next(queue, list_tail(queue), data);
}

int queue_dequeue(Queue *queue, void **data)
{
    /* Dequeue the data. */
    return list_remove_next(queue, NULL, data);
}