#ifndef DFS_H
#define DFS_H

#include "Database.h"
#include "Stadium.h"
#include "StadiumDistance.h"
#include "StadiumGraph.h"
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
#include <QHash>
#include <iostream>

using namespace std;

/*!
 * @brief Runs depth-first traversal algorithm using graph and startpoint
 * @param graph; Graph to reference for traversal
 * @param start; Starting point for traversal
 * @return QVector<StadiumDistance*>; Spanning tree resulting from traversal
 */
QVector<StadiumDistance*> DFS(const StadiumGraph& graph, Stadium* start);

// Creates & prints the specified path for DFS

/*!
 * @brief Creates and prints path specified by DFS traveresal
 * @param graph; Graph to reference for traversal
 * @param start; Starting point for traversal
 */
void runDFS(const StadiumGraph& graph, QString start);

// Runs / calls path for DFS from start stadium

/*!
 * @brief Method to test traversal algorithm
 */
void testDFS();

#endif // DFS_H
