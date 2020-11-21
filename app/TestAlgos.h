#ifndef TESTALGOS_H
#define TESTALGOS_H

#include "StadiumGraph.h"



// DIJKSTRA TEST FUNCTIONS
// Creates and prints the specified path for Dijkstra
void runDijkstra(const StadiumGraph& graph, QString start, QString end);

// Runs / calls various paths for Dijkstra
void testDijkstra();

// DFS TEST FUNCTIONS
// Creates & prints the specified path for DFS
void runDFS(const StadiumGraph& graph, QString start);

// Runs / calls path for DFS from start stadium
void testDFS();

#endif // TESTALGOS_H
