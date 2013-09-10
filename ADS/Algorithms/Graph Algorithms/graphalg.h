//
//  graphalg.h
//  ADS
//
//  Created by Vitaly Yurchenko on 09.09.13.
//  Copyright (c) 2013 Vitaly Yurchenko. All rights reserved.
//
// ********************************************************************************************************************************************************** //

#ifndef ADS_graphalg_h
#define ADS_graphalg_h

// ********************************************************************************************************************************************************** //

#include "graph.h"
#include "list.h"

// ********************************************************************************************************************************************************** //

/* Define a structure for vertices in minimum spanning trees. */
typedef struct MSTVertex_
{
    void *data;
    double weight;
    VertexColor color;
    double key;
    struct MSTVertex_ *parent;
} MSTVertex;

/* Define a structure for vertices in shortest-path problems. */
typedef struct PathVertex_
{
    void *data;
    double weight;
    VertexColor color;
    double d;
    struct PathVertex_ *parent;
} PathVertex;

/* Define a structure for vertices in traveling-salesman problems. */
typedef struct TSPVertex_
{
    void *data;
    double x;
    double y;
    VertexColor color;
} TSPVertex;

/* Public Interface. */

/*
 Description:   Computes a minimum spanning tree for an undirected, weighted graph specified by graph.
                The minimum spanning tree is computed starting from the vertex specified by start. The operation modifies graph,
                so a copy should be made before calling the operation, if necessary. Each vertex in graph must contain data of type MSTVertex.
                Assign a weight to each edge by setting the weight member of the MSTVertex structure passed as data2 to graph_ins_edge.
                Use the data member of each MSTVertex structure to store data associated with the vertex, such as an identifier.
                The match function for graph, which is set by the caller when initializing the graph with graph_init,
                should compare only the data members of MSTVertex structures. This is the same function that should be passed as the match argument to mst.
                Once computed, information about the minimum spanning tree is returned in span, which is a list of MSTVertex structures.
                In span, the vertex whose parent is set to NULL is the vertex at the root of the minimum spanning tree.
                The parent member of every other vertex points to the vertex that precedes it in the span.
                The vertices in span point to actual vertices in graph, so the caller must ensure that the storage in graph remains valid
                as long as span is being accessed. Use list_destroy to destroy span once it is no longer needed.
 
 Return Value:  0 if computing the minimum spanning tree is successful, or –1 otherwise.
 
 Complexity:    O(EV 2), where V is the number of vertices in the graph and E is the number of edges.
                However, with a little improvement to the implementation presented here, Prim’s algorithm runs in O(E lg V) time.
 */
int mst(Graph *graph, const MSTVertex *start, List *span, int (*match)(const void *key1, const void *key2));

/*
 Description:   Computes shortest paths between start and all other vertices in a directed, weighted graph specified by graph.
                The operation modifies graph, so a copy should be made before calling the operation, if necessary.
                Each vertex in graph must contain data of type PathVertex. Assign a weight to each edge
                by setting the weight member of the PathVertex structure passed as data2 to graph_ins_edge.
                Use the data member of each PathVertex structure to store data associated with the vertex, such as an identifier.
                The match function for graph, which is set by the caller when initializing the graph with graph_init,
                should compare only the data members of PathVertex structures. This is the same function that should be passed as the match argument
                to shortest. Once computed, information about the shortest paths is returned in paths, which is a list of PathVertex structures.
                In paths, the parent of the start vertex is set to NULL. The parent member of every other vertex points to the vertex that precedes it
                in the shortest path from the start vertex. The vertices in paths point to actual vertices in graph,
                so the caller must ensure that the storage in graph remains valid as long as paths is being accessed.
                Use list_destroy to destroy paths once it is no longer needed.
 
 Return Value:  0 if computing the shortest paths is successful, or –1 otherwise.
 
 Complexity:    O(EV2), where V is the number of vertices in the graph and E is the number of edges.
                However, with a little improvement, Dijkstra’s algorithm can run in O(E lg V) time.
 */
int shortest(Graph *graph, const PathVertex *start, List *paths, int (*match)(const void *key1, const void *key2));

/*
 Description:   Computes an approximate traveling-salesman tour of the points specified as vertices in vertices.
                The tour begins at the vertex specified by start. The operation modifies vertices, so a copy should be made before calling the operation,
                if necessary. Each element in vertices must be of type TSPVertex. Use the data member of each TSPVertex structure to store data
                associated with the vertex, such as an identifier. Use the x and y members of the structure to specify the coordinates
                associated with the vertex. The function specified by match determines whether two vertices match.
                It should only compare the data members of TSPVertex structures. The tour is returned in tour, which is a list of TSPVertex structures.
                Each vertex appears in tour in the order it would be encountered during the tour.
                The elements in tour point to the actual vertices in vertices, so the caller must ensure that the storage in vertices remains valid
                as long as tour is being accessed. Use list_destroy to destroy tour once it is no longer needed.
 
 Return Value:  0 if computing the approximate traveling-salesman tour is success- ful, or –1 otherwise.
 
 Complexity:    O(V2), where V is the number of vertices to visit in the tour.
 */
int tsp(List *vertices, const TSPVertex *start, List *tour, int (*match)(const void *key1, const void *key2));

// ********************************************************************************************************************************************************** //

#endif
