#ifndef DIJKSTRA_H
#define DIJKSTRA_H

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
 * @brief Finds shortest path from origin to all other vertices
 * @param graph; Graph for algorithm to reference
 * @param start; Starting vertex
 * @return QHash<QString, StadiumDistance*>; Spanning tree consisting of shortest paths
 */
QHash<QString, StadiumDistance*> Dijkstra(const StadiumGraph& graph, Stadium* start);

/*!
 * @brief Altered Dijkstras to function inside of loop to form overall shortest path given several inputs
 * @param graph; Graph for algorithm to reference
 * @param start; Starting vertex
 * @param visited; Overarching visited list to keep track of overall trip
 * @param distance; Overarching distance list to keep track of overall trip distance traveled
 * @return QString, StadiumDistance; Name of next vertex to visit
 */
QString NewTrips(const StadiumGraph& graph, Stadium* start, QStringList &visited, int &distance);

#endif // DIJKSTRA_H
