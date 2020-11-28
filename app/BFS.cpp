#include "BFS.h"
#include <QtDebug>
#include <QQueue>
#include <QMap>
#include "AdjacencyList.h"

BFS::BFS(AdjacencyList *list)
{
    aList = list;

    for(int index = 0; index < aList->list.size(); index++)
    {
        originNames.push_back(aList->list.at(index).origin);
    }

    distanceTraveled = 0;
    traversalList.clear();
}

void BFS::Traverse()
{
//    // DEBUG
//    qDebug() << "---- BFS START ----";

    QQueue<int> traversal;
    int currentCity;
    QString originName;

    // Create boolian visited list
    const int SIZE = aList->list.size();
    bool* visited = new bool [SIZE];

    // Insert starting city into traversal queue
    for(int index = 0; index < aList->list.size(); index++)
    {
        if(aList->list.at(index).origin == "SoFi Stadium")
        {
            // Mark as visited
            visited[index] = true;

            // Add to traversal list
            traversal.enqueue(index);

            // Add to output list
            traversalList.push_back("SoFi Stadium");
        }
    }

    // While the traversal list is not empty,
    while(!traversal.empty())
    {
        // Store starting point
        currentCity = traversal.front();

        // Pop starting point
        traversal.dequeue();

        // loop through connections to city at given point
        for(int index = 0; index < aList->list.at(currentCity).destinations.size(); index++)
        {
            // Find this name on the overall list
            for(int listIndex = 0; listIndex < aList->list.size(); listIndex++)
            {
                // If we find it on the list, and it's not visited
                if(aList->list.at(listIndex).origin == aList->list.at(currentCity).destinations.at(index).destination && !visited[listIndex])
                {
                    // Mark connection as visited
                    visited[listIndex] = true;

                    // Add node's index in overall list to traversal list
                    traversal.enqueue(listIndex);

                    // Add connection to output list
                    traversalList.push_back(aList->list.at(listIndex).origin);

                    distanceTraveled = distanceTraveled + aList->list.at(currentCity).destinations.at(index).distance;
                }
            }
        }
    }

//    // Print final traversal path
//    qDebug() << "Printing final path: ";
//    for(int index = 0; index < traversalList.size(); index++)
//    {
//        qDebug() << "City #" << index + 1 << ": " << traversalList.at(index);
//    }

//    qDebug() << "Distance Traveled: " << distanceTraveled;


//    qDebug() << "---- BFS END ----";
}


QStringList BFS::GetTraversalList() const
{
    return traversalList;
}

int BFS::GetDistanceTraveled() const
{
    return distanceTraveled;
}
