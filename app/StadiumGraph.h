#ifndef STADIUMGRAPH_H
#define STADIUMGRAPH_H

#include "Database.h"
#include "Stadium.h"
#include "StadiumDistance.h"

/*!
 * @struct StadiumGraph struct creates a graph from which to reference for various traversal algorithms
 */
struct StadiumGraph
{
    /// Stadium pointers in graph represent vertices
	QVector<Stadium*> cities;

    /// Adjacency list represents each vertex and its associated edge
    QHash<Stadium*, QVector<StadiumDistance*>> adjacencyList;

    // Utility function for the graph.  This doesn't run any queries
    // by itself, so it doesn't belong in Databse.
    // static because it's creating a graph instance which will be
    // shared across the app.
    // Called a factory function (like a named constructor).
    // included in the struct because it's a funtion of a graph.

    /*!
     * @brief Creates stadium graph object to be used by other modules to reference for traversal
     * @param *db; Pointer to database object
     * @return StadiumGraph; Graph used for traversal algorithms
     */
    static StadiumGraph createStadiumGraph(Database *db);

    /*!
     * @brief Test method used to print adjacency list
     */
    void printAdjList();
};

/*!
 * @brief Builds path given completed spanning tree and destination vertex
 * @param prev; Spanning tree created by traversal algorithm
 * @param destination; Vertex to create path toward
 * @return QVector<StadiumDistance*>; Path created from origin to destination
 */
QVector<StadiumDistance *> buildPath(QHash<QString, StadiumDistance*> prev, Stadium *destination);

/*!
 * @brief Test method to print path created by buildPath
 * @param path; Completed path from origin to destination via shortest path
 */
void printPath(QVector<StadiumDistance*> path);

#endif // STADIUMGRAPH_H
