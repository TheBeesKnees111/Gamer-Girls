#ifndef TESTALGOS_H
#define TESTALGOS_H

#include "StadiumGraph.h"

/*!
 * @brief Creates and prints the specified path for Dijkstra's algorithm
 * @param graph; Graph to reference during traversal
 * @param start; Starting vertex
 * @param end; Ending vertex
 */
void runDijkstra(const StadiumGraph& graph, QString start, QString end);

/*!
 * @brief Runs / calls various paths for Dijkstra's algorithm
 */
void testDijkstra();

/*!
 * @brief Creates & prints the specified path for depth-first search algorithm
 * @param graph; Graph to reference during traversal
 * @param start; Starting vertex
 */
void runDFS(const StadiumGraph& graph, QString start);

/*!
 * @brief Runs / calls path for depth-first search from starting vertex
 */
void testDFS();

#endif // TESTALGOS_H
