#include "BFS.h"
#include <QtDebug>
#include <QQueue>
#include <QMap>
#include "Database.h"

BFS::BFS()
{
    // Initialize matrix to zero
    for(int i = 0; i < 12; i++)
    {
        for(int j = 0; j < 12; j++)
        {
            matrix[i][j] = 0;
        }
    }

    // Initialize Test Distances
    Add(SEATTLE, SAN_FRANCISCO, 807);
    Add(SEATTLE, DENVER, 1331);
    Add(SEATTLE, CHICAGO, 2097);

    Add(SAN_FRANCISCO, LOS_ANGELES, 381);
    Add(SAN_FRANCISCO, DENVER, 1267);
    Add(SAN_FRANCISCO, SEATTLE, 807);

    Add(LOS_ANGELES, SAN_FRANCISCO, 381);
    Add(LOS_ANGELES, DENVER, 1015);
    Add(LOS_ANGELES, KANSAS_CITY, 1663);
    Add(LOS_ANGELES, DALLAS, 1435);

    Add(DENVER, SEATTLE, 1331);
    Add(DENVER, SAN_FRANCISCO, 1267);
    Add(DENVER, LOS_ANGELES, 1015);
    Add(DENVER, CHICAGO, 1003);
    Add(DENVER, KANSAS_CITY, 599);

    Add(CHICAGO, SEATTLE, 2097);
    Add(CHICAGO, DENVER, 1003);
    Add(CHICAGO, KANSAS_CITY, 533);
    Add(CHICAGO, BOSTON, 983);
    Add(CHICAGO, NEW_YORK, 787);

    Add(KANSAS_CITY, CHICAGO, 533);
    Add(KANSAS_CITY, DENVER, 599);
    Add(KANSAS_CITY, LOS_ANGELES, 1663);
    Add(KANSAS_CITY, DALLAS, 496);
    Add(KANSAS_CITY, ATLANTA, 864);
    Add(KANSAS_CITY, NEW_YORK, 1260);

    Add(DALLAS, LOS_ANGELES, 1435);
    Add(DALLAS, ATLANTA, 781);
    Add(DALLAS, KANSAS_CITY, 496);
    Add(DALLAS, HOUSTON, 239);

    Add(HOUSTON, DALLAS, 239);
    Add(HOUSTON, ATLANTA, 810);
    Add(HOUSTON, MIAMI, 1187);

    Add(ATLANTA, NEW_YORK, 888);
    Add(ATLANTA, KANSAS_CITY, 864);
    Add(ATLANTA, DALLAS, 781);
    Add(ATLANTA, HOUSTON, 810);
    Add(ATLANTA, MIAMI, 661);

    Add(NEW_YORK, BOSTON, 214);
    Add(NEW_YORK, CHICAGO, 787);
    Add(NEW_YORK, KANSAS_CITY, 1260);
    Add(NEW_YORK, ATLANTA, 888);

    Add(MIAMI, HOUSTON, 1187);
    Add(MIAMI, ATLANTA, 661);

    Add(BOSTON, CHICAGO, 983);
    Add(BOSTON, NEW_YORK, 214);

    // Initialize City Names
    // Load names into cityname list
    stadiumNames = new QStringList;
    stadiumNames->push_back("Seattle");
    stadiumNames->push_back("San Francisco");
    stadiumNames->push_back("Los Angeles");
    stadiumNames->push_back("Denver");
    stadiumNames->push_back("Kansas City");
    stadiumNames->push_back("Dallas");
    stadiumNames->push_back("Chicago");
    stadiumNames->push_back("Houston");
    stadiumNames->push_back("Atlanta");
    stadiumNames->push_back("New York");
    stadiumNames->push_back("Miami");
    stadiumNames->push_back("Boston");


//    // DEBUG TODO TESTING ONLY. IN PRACTICE, PASS A POINTER TO QSTRINGLIST INTO PARAMETERIZED CONSTRUCTOR
//    Database* db = new Database;

//    // Initialize Stadium Names List
//    stadiumNames = db->GetBFSStadiums();

}

void BFS::Add(const int &from, const int &to, const int &distance)
{
    matrix[from][to] = distance;
}


void BFS::Traverse()
{
    qDebug() << "---- BFS START ----";

    QQueue<int> traversal;
    QMap<int, QString> neighbors;
    QMap<int, QString>::iterator it;
    const int MATRIX_SIZE = 12;
    int distanceTraveled = 0;
    QVector<QString> traversalOutput;

    // Insert starting city into traversal queue
    traversal.enqueue(KANSAS_CITY);

    // Mark starting city as visited
    visited[KANSAS_CITY] = true;
    traversalOutput.push_back("Kansas City");

    // While the traversal list is not empty,
    while(!traversal.empty())
    {
        qDebug() << "Arriving at: " << stadiumNames->at(traversal.head());
        // Store location of front of queue
        int row = traversal.front();

        // Pop city
        traversal.dequeue();

        // Check matrix for neighbors
        for(int column = 0; column < MATRIX_SIZE; column++)
        {
            // Find all neighbors of current city that have not been visited
            if(matrix[row][column] > 0 && !visited[column])
            {
                // Add distance and cityname to neighbors map (ordered map)
                neighbors.insert(matrix[row][column], stadiumNames->at(column));

                // Sum distance traveled;
                distanceTraveled = distanceTraveled + matrix[row][column];

                // Mark this city as visited
                visited[column] = true;
            }// End find unvisited neighbors
            else if(matrix[row][column] > 0 && visited[column])
            {
                qDebug() << "Cross Edge: " << stadiumNames->at(column);
            }
        }// End find neighbors

        // Insert all neighbors into queue
        for(it = neighbors.begin(); it != neighbors.end(); ++it)
        {
            for(int index = 0; index < stadiumNames->size(); index++)
            {
                // If the name matches, add the matrix location to the queue
                if(it->contains(stadiumNames->at(index)))
                {
                    traversal.enqueue(index);
                    qDebug() << "Discovery Edge: " << stadiumNames->at(traversal.last());
                }
            }
        }// End insert neighbors

        // If queue not empty, insert name into output vector
        if(!traversal.empty())
        {
            traversalOutput.push_back(stadiumNames->at(traversal.head()));
        }

        // Clear neighbors list
        neighbors.clear();
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
