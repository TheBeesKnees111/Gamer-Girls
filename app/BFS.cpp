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
}

void BFS::Traverse()
{
    qDebug() << "---- BFS START ----";

    QQueue<AdjacencyList::Vertex> traversal;
    QString originName;
    int distanceTraveled = 0;
    QVector<QString> traversalOutput;

    AdjacencyList::Vertex origin;

    // Insert starting city into traversal queue
    for(int index = 0; index < aList->list.size(); index++)
    {
        if(aList->list.at(index).origin == "SoFi Stadium")
        {
            // Mark as visited
            aList->list.operator[](index).visited = true;

            // Add to traversal list
            traversal.enqueue(aList->list.at(index));

            // Add to output list
            traversalOutput.push_back("SoFi Stadium");
        }
        else
        {
            qDebug() << "SoFi Stadium not found";
        }
    }

    // While the traversal list is not empty,
    while(!traversal.empty())
    {
        qDebug() << "Arriving at: " << traversal.head().origin;

        origin = traversal.head();

        // Pop city
        traversal.dequeue();

        // Check this list position for neighbors
        for(int index = 0; index < origin.destinations.size(); index++)
        {
            // Find all neighbors of current city that have not been visited
            if(origin.destinations.at(index).distance > 0 && !origin.destinations.at(index).visited)
            {
                originName = origin.destinations.at(index).destination;

                // Mark as visited
                aList->list.operator[](index).visited = true;

                // Add to traversal list
                traversal.enqueue(aList->list.at(index));

                // Add to output list
                traversalOutput.push_back(originName);

                qDebug() << "Discovery Edge: " << originNames.at((traversal.back()));

                // Sum distance traveled;
                distanceTraveled = distanceTraveled + origin.destinations.at(index).distance;

            }// End find unvisited neighbors
            else if(origin.destinations.at(index).distance > 0 && origin.destinations.at(index).visited)
            {
                qDebug() << "Cross Edge: " << originNames.at(index);
            }
        }// End find neighbors

        // ISNT IT SUPPOSED TO POP?!

    }

    // Print final traversal path
    qDebug() << "Printing final path: ";
    for(int index = 0; index < traversalOutput.size(); index++)
    {
        qDebug() << "City #" << index + 1 << ": " << traversalOutput.at(index);
    }

    qDebug() << "Distance Traveled: " << distanceTraveled;


    qDebug() << "---- BFS END ----";
}
