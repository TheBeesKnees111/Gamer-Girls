#include "StadiumGraph.h"
#include <iostream>
using namespace std;


// This creates a graph of Stadiums.  It is an adjacency list made
// using a map(hash) of vectors.  The key for each entry is the Stadium,
// and the value is a vector of adjacent edges (StadiumDistances).
StadiumGraph StadiumGraph::createStadiumGraph(Database *db)
{
    // create edgeList (adjacent nodes)
    QVector<StadiumDistance*> edgeList = db->getStadiumDistances();
    // adjacencyList of key (Stadium) and Vector of adjacent edges(StadiumDistance)
    QHash<Stadium*, QVector<StadiumDistance*>> adjacencyList;

    // Creates adjacencyList from the edge list
    for(auto edge : edgeList)
    {
        Stadium* fromStadium = edge->getFromStadium();

        if (fromStadium != edge->getToStadium())
        {
            // Creates adjacencyList if it doesn't already exist
            adjacencyList[fromStadium].push_back(edge);
        }
    }
    // creating graph when returning
    return {db->getStadiums(), adjacencyList};
}

// prints adjacency list
void StadiumGraph::printAdjList()
{
    for (auto stadium : adjacencyList.keys())
    {
        cout << stadium->getStadiumName().toStdString()
             << " at " << stadium->getLocation().toStdString() << endl;
       for ( auto neighbor : adjacencyList[stadium])
       {
            cout << "\t=> " << neighbor->getToStadium()->getStadiumName().toStdString()
                 << " (" << neighbor->getDistance() << ")"
                 << endl;
       }
    }
}

// given a spanning tree (Dijkstra, DFS) and a destination Stadium,
// trace the path from the given node(destination) to the root(origin)
QVector<StadiumDistance *> buildPath(QHash<QString, StadiumDistance*> prev, Stadium *destination)
{
    //1  S ← empty sequence
    QVector<StadiumDistance*> S; // TODO rename to path
    //2  u ← endLocation
    Stadium *currentStadium = destination;
    //3  if prev[u] is defined or u = start:
    // Do something only if the vertex is reachable
    if(prev[currentStadium->getStadiumName()] != nullptr)
    {
        //4      while u is defined:
        // Construct the shortest path with a stack S
        while (currentStadium != nullptr)
        {
            //5          insert u at the beginning of S
            // Push the vertex onto the stack
            //6          u ← prev[u]
            // Traverse from endLocation to start
            StadiumDistance *parent = prev[currentStadium->getStadiumName()];

            if (parent != nullptr)
            {
                S.push_back(parent);
                currentStadium = parent->getFromStadium();
            }
            else
                currentStadium = nullptr;
        }
        reverse(S.begin(), S.end());
    }
    return S;
}

// prints the selected path
void printPath(QVector<StadiumDistance*> path)
{
    int totalMiles = 0;
    cout << "Shortest path: " << endl;
    for (auto DistanceNode : path)
    {
        Stadium *fromStadium = DistanceNode->getFromStadium();
        Stadium *toStadium = DistanceNode->getToStadium();
        cout << fromStadium->getStadiumName().toStdString()
             << " at " << fromStadium->getLocation().toStdString()
             << " === " << DistanceNode->getDistance() << " ===> "
             << toStadium->getStadiumName().toStdString()
             << " at " << toStadium->getLocation().toStdString()
             << endl;
            totalMiles += DistanceNode->getDistance();
    }
    cout <<"\tTOTAL MILES: " << totalMiles << endl;
}
