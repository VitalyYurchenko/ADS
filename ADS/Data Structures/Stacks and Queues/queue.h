//
//  queue.h
//  ADS
//
//  Created by Vitaly Yurchenko on 8/31/13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_queue_h
#define ADS_queue_h

// ********************************************************************************************************************************************************** //

#include "list.h"

// ********************************************************************************************************************************************************** //

/* Implement queues as linked lists. */
typedef List Queue;

/* Public Interface. */
#define queue_init list_init
#define queue_destroy list_destroy
int queue_enqueue(Queue *queue, const void *data);
int queue_dequeue(Queue *queue, void **data);
#define queue_peek(queue) ((queue)->head == NULL ? NULL : (queue)->head->data)
#define queue_size list_size

// ********************************************************************************************************************************************************** //

#endif
