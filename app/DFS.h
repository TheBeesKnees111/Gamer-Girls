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

using namespace std;

// single source shortest path from a given start.
// building whole spanning tree of the shortest paths from the start stadium
// to all other stadiums.
// returns the complete spanning tree which can be used for multiple searches
// for the shortest path.
//QHash<QString, StadiumDistance*> DFS(const StadiumGraph& graph, Stadium* start);
QVector<StadiumDistance*> DFS(const StadiumGraph& graph, Stadium* start);

#endif // DFS_H
