#include "Dijkstra.h"
#include <iostream>
#include <queue>
#include <QMap>


QHash<QString, StadiumDistance*> Dijkstra(const StadiumGraph& graph, Stadium *start)
{
    //1  function Dijkstra(Graph, start):
    //2
    //3      create vertex set pending
    QHash<QString, int> dist;
    QHash<QString, StadiumDistance*> prev;        // parent map
    // gave the priority queue a lambda to determine the priority of a stadium
    priority_queue<Stadium*, vector<Stadium*>, function<bool(Stadium*, Stadium*)>>
        pending { [&dist](Stadium* lhs, Stadium* rhs)
        {return dist[lhs->getStadiumName()] < dist[rhs->getStadiumName()];} };

    //4
    //5      for each vertex v in Graph:
    for (auto node : graph.cities)
    {
        //6          dist[v] ← INFINITY
        dist[node->getStadiumName()] = numeric_limits<int>::max(); // (largest positive 32 bit #)
        //7          prev[v] ← UNDEFINED
        prev[node->getStadiumName()] = nullptr;
        //8          add v to pending
//        pending.push(node);
    }

    //10      dist[start] ← 0
    dist[start->getStadiumName()] = 0;
    //11
    // loop thru start's adjacent vertices & add them to the pending list
    for (auto neighbor : graph.adjacencyList[start])
    {
        Stadium *toStadium = neighbor->getToStadium();
        dist[toStadium->getStadiumName()] = neighbor->getDistance();
        prev[toStadium->getStadiumName()] = neighbor;
        pending.push(toStadium);
    }
    //12      while pending is not empty:
    while (!pending.empty())
    {
        //13          u ← vertex in pending with min dist[u]
        Stadium *currentStadium = pending.top();
        //14
        //15          remove u from pending
        pending.pop();
        //16
        //17          for each neighbor v of u:
        // only v that are still in pending
        for (auto adjacent : graph.adjacencyList[currentStadium])
        {
            //18              alt ← dist[u] + length(u, v)
            int alt = dist[currentStadium->getStadiumName()] + adjacent->getDistance();
            //19              if alt < dist[v]:
            if (alt < dist[adjacent->getToStadium()->getStadiumName()])
            {
                //20                  dist[v] ← alt
                dist[adjacent->getToStadium()->getStadiumName()] = alt;
                //21                  prev[v] ← u
                prev[adjacent->getToStadium()->getStadiumName()] = adjacent;
            }
        }
        //22
    }
    //23      return dist[], prev[]
    return prev;
}

// given a spanning tree and a given node,
// trace the path from the given node to the root(origin)
QVector<StadiumDistance *> buildPath(QHash<QString, StadiumDistance*> prev, Stadium *destination)
{
    //1  S ← empty sequence
    QVector<StadiumDistance*> S;
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
//            S.push_back(currentStadium->getStadiumName());

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


void printDijkstra(QVector<StadiumDistance*> path)
{
    int totalMiles = 0;
    cout << "Shortest path: " << endl;
    for (auto DistanceNode : path)
    {
        cout << DistanceNode->getFromStadium()->getStadiumName().toStdString()
             << " === " << DistanceNode->getDistance() << " ===> "
        << DistanceNode->getToStadium()->getStadiumName().toStdString() << endl;
            totalMiles += DistanceNode->getDistance();
    }
    cout <<"\tTOTAL MILES: " << totalMiles << endl;
}

//bool operator< (const Stadium& lhs, const Stadium& rhs)
//{
//    return (lhs.name < rhs.name);
//}

