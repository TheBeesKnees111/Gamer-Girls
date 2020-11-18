#ifndef STADIUMGRAPH_H
#define STADIUMGRAPH_H

#include "Database.h"
#include "Stadium.h"
#include "StadiumDistance.h"

// Graph of cities and their connections
struct StadiumGraph
{
    QVector<Stadium*> cities;
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

void printPath(QVector<StadiumDistance*> path);

#endif // STADIUMGRAPH_H
