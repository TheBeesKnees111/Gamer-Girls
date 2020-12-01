#ifndef BFS_H
#define BFS_H
#include <QList>
#include <QString>
#include <QVector>
#include "AdjacencyList.h"

/*!
 * @class BFS
 * @brief The BFS class contains all objects necessary to run breadth first search traversal of graph
 */
class BFS
{
public:
    /*!
     * @brief Parameterized constructor populates list
     * @param list; AdjacencyList object to populate and use in traversal
     */
    BFS(AdjacencyList *list);

    /*!
     * @brief Performs traversal. Will populate traversal list and distance traveled
     */
    void Traverse();

    /*!
     * @brief Accessor will return list in order of traversal
     * @return QStringList; Traversal list in order of traversal
     */
    QStringList GetTraversalList() const;

    /*!
     * @brief Accessor will return total weight of edges traversed
     * @return int; Sum of edge weights
     */
    int GetDistanceTraveled() const;

private:
    /// Adjacency list object referenced in traversal
    AdjacencyList* aList;
    /// Names associated with vertices to traverse
    QVector<QString> originNames;
    /// Total weight of edges traversed
    int distanceTraveled;
    /// Final list of vertices traversed in order of traversal
    QStringList traversalList;
};

#endif // BFS_H
