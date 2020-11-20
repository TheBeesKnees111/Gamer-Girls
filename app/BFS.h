#ifndef BFS_H
#define BFS_H
#include <QList>
#include <QString>
#include <QVector>
#include "AdjacencyList.h"

class BFS
{
public:
    // Parameterized constructor populates list
    BFS(AdjacencyList *list);

    // Performs traversal. Pass in blank list of names and int 0 to return
    // list of names populated in order of traversal and distance traveled on trip
    void Traverse();

    // Returns list of team names in order of traversal
    QStringList GetTraversalList() const;

    // Return distance traveled over traversal
    int GetDistanceTraveled() const;
private:
    AdjacencyList* aList;
    QVector<QString> originNames;
    int distanceTraveled;
    QStringList traversalList;


};

#endif // BFS_H
