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
        /// Name of destination vertex
        QString destination;
        /// Weight of connection between vertices
        int distance;
    };

    /*!
     * @brief Vertex struct represents a vertex on a graph
     */
    struct Vertex
    {
        /// Name of origin vertex
        QString origin;
        /// List of connections from this vertex
        QList<Edge> destinations;
    };

    /// Internal list to contain adjacency list
    QVector<Vertex> list;

    /*!
     * @brief Default constructor
     */
    AdjacencyList();
};

#endif // ADJACENCYLIST_H
