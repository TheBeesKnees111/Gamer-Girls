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

// single source shortest path from a given start.
// building whole spanning tree of the shortest paths from the start stadium
// to all other stadiums.
// returns the complete spanning tree which can be used for multiple searches
// for the shortest path.
QHash<QString, StadiumDistance*> Dijkstra(const StadiumGraph& graph, Stadium* start);

void runDijkstra(const StadiumGraph& graph, QString start, QString end);

void testDijkstra();

#endif // DIJKSTRA_H
