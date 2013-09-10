//
//  parcels.c
//  ADS
//
//  Created by Vitaly Yurchenko on 10.09.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "parcels.h"

#include <stdlib.h>
#include <string.h>

// ********************************************************************************************************************************************************** //

int get_parcel(PQueue *parcels, Parcel *parcel)
{
    Parcel *data;
    
    if (pqueue_size(parcels) == 0)
    {
        /* Return that there are no parcels. */
        return -1;
    }
    else
    {
        if (pqueue_extract(parcels, (void **)data) != 0)
        {
            /* Return that a parcel could not be retrieved. */
            return -1;
        }
        else
        {
            /* Pass back the highest-priority parcel. */
            memcpy(parcel, data, sizeof(Parcel));
            
            free(data);
        }
    }
    
    return 0;
}

int put_parcel(PQueue *parcels, const Parcel *parcel)
{
    Parcel *data;
    
    /* Allocate storage for the parcel. */
    if ((data = (Parcel *)malloc(sizeof(Parcel))) == NULL)
    {
        return -1;
    }
    
    /* Insert the parcel into the priority queue. */
    memcpy(data, parcel, sizeof(Parcel));
    
    if (pqueue_insert(parcels, data) != 0)
    {
        return -1;
    }
    
    return 0;
}
