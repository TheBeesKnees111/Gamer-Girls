#include "BFS.h"
#include <QtDebug>
#include <QQueue>
#include <QMap>
#include "AdjacencyList.h"

BFS::BFS(AdjacencyList *list)
{
    aList = list;
}

void BFS::Traverse()
{
//    qDebug() << "---- BFS START ----";

//    QQueue<int> traversal;
//    QMap<int, QString> neighbors;
//    QMap<int, QString>::iterator it;
//    const int MATRIX_SIZE = 12;
//    int distanceTraveled = 0;
//    QVector<QString> traversalOutput;

//    // Insert starting city into traversal queue
//    traversal.enqueue(KANSAS_CITY);

//    // Mark starting city as visited
//    visited[KANSAS_CITY] = true;
//    traversalOutput.push_back("Kansas City");

//    // While the traversal list is not empty,
//    while(!traversal.empty())
//    {
//        qDebug() << "Arriving at: " << stadiumNames->at(traversal.head());
//        // Store location of front of queue
//        int row = traversal.front();

//        // Pop city
//        traversal.dequeue();

//        // Check matrix for neighbors
//        for(int column = 0; column < MATRIX_SIZE; column++)
//        {
//            // Find all neighbors of current city that have not been visited
//            if(matrix[row][column] > 0 && !visited[column])
//            {
//                // Add distance and cityname to neighbors map (ordered map)
//                neighbors.insert(matrix[row][column], stadiumNames->at(column));

//                // Sum distance traveled;
//                distanceTraveled = distanceTraveled + matrix[row][column];

//                // Mark this city as visited
//                visited[column] = true;
//            }// End find unvisited neighbors
//            else if(matrix[row][column] > 0 && visited[column])
//            {
//                qDebug() << "Cross Edge: " << stadiumNames->at(column);
//            }
//        }// End find neighbors

//        // Insert all neighbors into queue
//        for(it = neighbors.begin(); it != neighbors.end(); ++it)
//        {
//            for(int index = 0; index < stadiumNames->size(); index++)
//            {
//                // If the name matches, add the matrix location to the queue
//                if(it->contains(stadiumNames->at(index)))
//                {
//                    traversal.enqueue(index);
//                    qDebug() << "Discovery Edge: " << stadiumNames->at(traversal.last());
//                }
//            }
//        }// End insert neighbors

//        // If queue not empty, insert name into output vector
//        if(!traversal.empty())
//        {
//            traversalOutput.push_back(stadiumNames->at(traversal.head()));
//        }

//        // Clear neighbors list
//        neighbors.clear();
//    }

//    // Print final traversal path
//    qDebug() << "Printing final path: ";
//    for(int index = 0; index < traversalOutput.size(); index++)
//    {
//        qDebug() << "City #" << index + 1 << ": " << traversalOutput.at(index);
//    }

//    qDebug() << "Distance Traveled: " << distanceTraveled;


//    qDebug() << "---- BFS END ----";
}
