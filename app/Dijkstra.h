#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "Stadium.h"
#include "StadiumDistance.h"
#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
#include <QMap>

using namespace std;


// Node of a city
//struct StadiumNode
//{
//    string name;
//};

//bool operator< (const StadiumNode& lhs, const StadiumNode& rhs);

// Connection between two cities
//struct StadiumConnection
//{
//    StadiumNode fromStadium;
//    StadiumNode toStadium;
//    int         milesBetween;
//};

// Graph of cities and their connections
struct StadiumGraph
{
    QVector<Stadium*> cities;
    QMap<Stadium*, QVector<StadiumDistance*>> adjacencyList;
};

// single source shortest path from a given start.
// building whole spanning tree of the shortest paths from the start stadium
// to all other stadiums.
// returns the complete spanning tree which can be used for multiple searches
// for the shortest path.
QMap<QString, StadiumDistance*> Dijkstra(const StadiumGraph& graph, Stadium* start);

// given any spanning tree and a given node,
// trace the path from the given node to the root(origin)
QVector<StadiumDistance *> buildPath(QMap<QString, StadiumDistance*> prev, Stadium *destination);

// FIXME printed path is empty.  Need to stop thru the debugger from here
void printDijkstra(QVector<StadiumDistance*> path);

#endif // DIJKSTRA_H
