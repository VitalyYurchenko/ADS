//
//  list.h
//  ADS
//
//  Created by Vitaly Yurchenko on 29.08.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_list_h
#define ADS_list_h

// ********************************************************************************************************************************************************** //

/* Define structure for linked list elements. */
typedef struct ListElmt_
{
    void *data;
    struct ListElmt_ *next;
} ListElmt;

/* Define structure for linked lists. */
typedef struct List_
{
    int size;
    int (*match)(const void *key1, const void *key2);
    void (*destroy)(void *data);
    ListElmt *head;
    ListElmt *tail;
} List;

/* Public interface. */
void list_init(List *list, void (*destroy)(void *data));
void list_destroy(List *list);
int list_insert_next(List *list, ListElmt *element, const void *data);
int list_remove_next(List *list, ListElmt *element, void **data);
#define list_size(list) ((list)->size)
#define list_head(list) ((list)->head)
#define list_tail(list) ((list)->tail)
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
#define list_data(element) ((element)->data)
#define list_next(element) ((element)->next)

// ********************************************************************************************************************************************************** //

#endif
