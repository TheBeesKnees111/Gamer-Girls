#include "Dijkstra.h"
#include <iostream>
#include <queue>
#include <QMap>

//1  function Dijkstra(Graph, start):
QHash<QString, StadiumDistance*> Dijkstra(const StadiumGraph& graph, Stadium *start)
{
    //3      create vertex set pending
    QHash<QString, int> dist;
    QHash<QString, StadiumDistance*> prev;        // parent map
    // gave the priority queue a lambda to determine the priority of a stadium
    priority_queue<Stadium*, vector<Stadium*>, function<bool(Stadium*, Stadium*)>>
        pending { [&dist](Stadium* lhs, Stadium* rhs){
        return dist[lhs->getStadiumName()] < dist[rhs->getStadiumName()];
    }};
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
    //15          remove u from pending
    pending.pop();
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
              pending.push(adjacent->getToStadium());
          }
      }
  }
//23      return dist[], prev[]
return prev;
}

