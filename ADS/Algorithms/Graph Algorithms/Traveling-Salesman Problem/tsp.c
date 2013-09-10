//
//  tsp.c
//  ADS
//
//  Created by Vitaly Yurchenko on 09.09.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#include "graphalg.h"

#include <float.h>
#include <math.h>
#include <stdio.h>

// ********************************************************************************************************************************************************** //

int tsp(List *vertices, const TSPVertex *start, List *tour, int (*match)(const void *key1, const void *key2))
{
    TSPVertex *tsp_vertex;
    TSPVertex *tsp_start;
    TSPVertex *selection;
    ListElmt *element;
    double minimum;
    double distance;
    double x;
    double y;
    int found;
    int i;
    
    /* Initialize the list for the tour. */
    found = 0;
    
    for (element = list_head(vertices); element != NULL; element = list_next(element))
    {
        tsp_vertex = list_data(element);
        
        if (match(tsp_vertex, start))
        {
            /* Start the tour at the start vertex. */
            if (list_insert_next(tour, list_tail(tour), tsp_vertex) != 0)
            {
                list_destroy(tour);
                
                return -1;
            }
            
            /* Save the start vertex and its coordinates. */
            tsp_start = tsp_vertex;
            x = tsp_vertex->x;
            y = tsp_vertex->y;
            
            /* Color the start vertex black. */
            tsp_vertex->color = black;
            
            found = 1;
        }
        else
        {
            /* Color all other vertices white. */
            tsp_vertex->color = white;
        }
    }
    
    /* Return if the start vertex was not found. */
    if (!found)
    {
        list_destroy(tour);
        
        return -1;
    }
    
    /* Use the nearest-neighbor heuristic to compute the tour. */
    i = 0;
    
    while (i < list_size(vertices) - 1)
    {
        /* Select the white vertex closest to the previous vertex in the tour. */
        minimum = DBL_MAX;
        
        for (element = list_head(vertices); element != NULL; element = list_next(element))
        {
            tsp_vertex = list_data(element);
            
            if (tsp_vertex->color == white)
            {
                distance = sqrt(pow(tsp_vertex->x - x, 2.0) + pow(tsp_vertex->y - y, 2.0));
                
                if (distance < minimum)
                {
                    minimum = distance;
                    selection = tsp_vertex;
                }
            }
        }
        
        /* Save the coordinates of the selected vertex. */
        x = selection->x;
        y = selection->y;
        
        /* Color the selected vertex black. */
        selection->color = black;
        
        /* Insert the selected vertex into the tour. */
        if (list_insert_next(tour, list_tail(tour), selection) != 0)
        {
            list_destroy(tour);
            
            return -1;
        }
        
        /* Prepare to select the next vertex. */
        i++;
    }
    
    /* Insert the start vertex again to complete the tour. */
    if (list_insert_next(tour, list_tail(tour), tsp_start) != 0)
    {
        list_destroy(tour);
        
        return -1;
    }
    
    return 0;
}
