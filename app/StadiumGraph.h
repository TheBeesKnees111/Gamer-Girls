#ifndef STADIUMGRAPH_H
#define STADIUMGRAPH_H

#include "Database.h"
#include "Stadium.h"
#include "StadiumDistance.h"

// Graph of cities and their connections
// The QHash (map) will have a vector of all the Stadiums,
// as well as an adjacencyList with a key = Stadium
// and value = vecor of adjacent Edges (StadiumDistances)
struct StadiumGraph
{
    // vector of Stadiums* in graph
    QVector<Stadium*> Stadiums;

    // map of key = Stadium*, value = vector of Edges(StadiumDistance*)
    QHash<Stadium*, QVector<StadiumDistance*>> adjacencyList;

    // Utility function for the graph.  This doesn't run any queries
    // by itself, so it doesn't belong in Databse.
    // static because it's creating a graph instance which will be
    // shared across the app.
    // Called a factory function (like a named constructor).
    // included in the struct because it's a funtion of a graph.
    static StadiumGraph createStadiumGraph(Database *db);

    void printAdjList();
};

// GRAPH UTILITIES
// given any spanning tree and a given node,
// trace the path from the given node to the root(origin)
QVector<StadiumDistance *> buildPath(QHash<QString, StadiumDistance*> prev, Stadium *destination);

// print that path
void printPath(QVector<StadiumDistance*> path);

#endif // STADIUMGRAPH_H
