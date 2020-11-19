#ifndef BFS_H
#define BFS_H
#include <QList>
#include <QString>
#include <QVector>
#include "AdjacencyList.h"

class BFS
{
public:
    // Performs traversal
    void Traverse();

    // Parameterized constructor populates list
    BFS(AdjacencyList *list);
private:
    AdjacencyList* aList;
    QVector<QString> originNames;
};

#endif // BFS_H
