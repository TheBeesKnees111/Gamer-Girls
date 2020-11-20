#include "DFS.h"
#include <iostream>
#include <QStack>
#include <QMap>
using namespace std;

// DFS method
// Returns the shortest path
// Preconditions: Needs an AdjacencyList and starting city
// Postconditions: Returns a path vector of CityNodes
QVector<StadiumDistance*> DFS(const StadiumGraph& graph, Stadium *start)
//QHash<QString, StadiumDistance*> DFS(const StadiumGraph& graph, Stadium *start)
{
    //pending (container of nodes to process)
    QStack<StadiumDistance*> pending;

    // list of visited cities
    QHash<QString, StadiumDistance*> visited;        // parent map

    // path for DFS
    QVector<StadiumDistance*> path;

    // sort adjacencyList for the start stadium
    vector<StadiumDistance*> neighbors = graph.adjacencyList[start].toStdVector();
    sort(neighbors.begin(), neighbors.end(),
         // lambda for sort
         [] (StadiumDistance *lhs, StadiumDistance *rhs)
        {return lhs->getDistance() > rhs->getDistance();} );

    // loop thru start's adjacent vertices & add them to the pending list
    // fills the stack for while loop, biggest to smallest distance
    // so that the first to be popped off will be the smallest distance
    for (auto neighbor : neighbors)
    {
        pending.push(neighbor);
    }

    // initalizing root node
    visited[start->getStadiumName()] = nullptr;

    // while pending is not empty:
    while (!pending.empty())
    {
        // vertex in pending with min dist[u]
        StadiumDistance *currentEdge = pending.top();
       //15          remove u from pending
        pending.pop();
        // retrieve next node to process
        Stadium *currentStadium = currentEdge->getToStadium();
//        Stadium *previousStadium = currentEdge->getFromStadium();

        // if not already visited
        if (!visited.contains(currentStadium->getStadiumName()))
        {
            // add to visited list & path
            visited[currentStadium->getStadiumName()] = currentEdge;
            path.push_back(currentEdge);

            // sort that stadium's adjacent edges
            vector<StadiumDistance*> neighbors = graph.adjacencyList[currentStadium].toStdVector();
            sort(neighbors.begin(), neighbors.end(),
                 [] (StadiumDistance *lhs, StadiumDistance *rhs)
                {return lhs->getDistance() > rhs->getDistance();} );

            // add them to the list to process
            for (auto adjacent : neighbors)
            {
                    pending.push(adjacent);
            }
        }
    }
    return path;
}

// Creates & prints the specified path for DFS
void runDFS(const StadiumGraph& graph, QString start)
{
    Database* db = Database::getInstance();

    Stadium* startLocation{db->getStadiumByName(start)};

    // Create the DFS starting from this location
    QVector<StadiumDistance*> spanningTree = DFS(graph, startLocation);

    cout << "===================================================================" << endl;
    cout << "DFS PATH FROM " << start.toStdString() <<  endl;
    cout << "===================================================================" << endl;

    // Print the path
    printPath(spanningTree);
}

// Runs / calls path for DFS from start stadium
void testDFS()
{
    // Create Database
    Database* db = Database::getInstance();

    StadiumGraph graph = StadiumGraph::createStadiumGraph(db);
//    graph.printAdjList();

//    runDFS(graph, "Soldier Field");
//    runDFS(graph, "SoFi Stadium");
//    runDFS(graph, "Gillette Stadium");
//    runDFS(graph, "Lincoln Financial Field");
//    runDFS(graph, "Bank of America Stadium");
//    runDFS(graph, "Allegiant Stadium");
    runDFS(graph, "U.S. Bank Stadium");
}
