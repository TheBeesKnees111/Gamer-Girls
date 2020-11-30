#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include <QString>
#include <QList>
#include <QVector>
#include "Database.h"

/*!
 * @class AdjacencyList
 * @brief The AdjacencyList class is an object that contains an adjacency list used in breadth first search
 */
class AdjacencyList
{
public:

    /*!
     * @brief Edge struct represents edge on a graph
     */
    struct Edge
    {
        QString destination; /// Name of destination vertex
        int distance; /// Weight of connection between vertices
    };

    /*!
     * @brief Vertex struct represents a vertex on a graph
     */
    struct Vertex
    {
        QString origin; /// Name of origin vertex
        QList<Edge> destinations; /// List of connections from this vertex
    };

    QVector<Vertex> list; /// Internal list to contain adjacency list

    /*!
     * @brief Default constructor
     */
    AdjacencyList();
};

#endif // ADJACENCYLIST_H
