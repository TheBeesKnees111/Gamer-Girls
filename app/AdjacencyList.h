#ifndef ADJACENCYLIST_H
#define ADJACENCYLIST_H
#include <QString>
#include <QList>
#include <QVector>
#include "Database.h"

class AdjacencyList
{
public:
    struct Edge
    {
        QString endCity;
        int distance;
    };

    struct Vertex
    {
        QString startCity;
        QList<Edge> destinations;
        bool visited;
    };

    QVector<Vertex> list;

    AdjacencyList();
};

#endif // ADJACENCYLIST_H
