//
//  route.h
//  ADS
//
//  Created by Vitaly Yurchenko on 10.09.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_route_h
#define ADS_route_h

// ********************************************************************************************************************************************************** //

#include "graphalg.h"

// ********************************************************************************************************************************************************** //

/* Public Interface. */
int route(List *paths, PathVertex *destination, PathVertex **next, int (*match)(const void *key1, const void *key2));

// ********************************************************************************************************************************************************** //

#endif
