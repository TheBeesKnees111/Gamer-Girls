#ifndef BFS_H
#define BFS_H
#include <QList>
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
};

#endif // BFS_H
