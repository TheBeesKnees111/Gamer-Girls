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

using namespace std;

/*!
 * @brief Dijkstra finds shortest paths from start stadium
 * @param graph; Graph of all stadiums
 * @param start; Beginning stadium
 */
// single source shortest path from a given start.
// building whole spanning tree of the shortest paths from the start stadium
// to all other stadiums. Returns the complete spanning tree which can be used
// for multiple searches for the shortest path from the start location.
QHash<QString, StadiumDistance*> Dijkstra(const StadiumGraph& graph, Stadium* start);

// Creates and prints the specified path for Dijkstra
void runDijkstra(const StadiumGraph& graph, QString start, QString end);

// Runs / calls various paths for Dijkstra
void testDijkstra();

#endif // DIJKSTRA_H
