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

QStringList RecursiveDijkstras(QStringList stadiumNames, const StadiumGraph& graph, Stadium *start)
{





    QHash<QString, bool> visited;
    QStringList tripList;

    for(int index = 0; index < stadiumNames.size(); index++)
    {
        visited.insert(stadiumNames.at(index), false);
    }

    Helper(graph, start, visited, tripList);

    qDebug() << tripList;

    return tripList;
}

// Recursive helper
void Helper(const StadiumGraph& graph, Stadium *start, QHash<QString, bool> &visited, QStringList &tripList)
{
    QHash<QString, int> dist; // Cost array
    QHash<QString, bool>::iterator visitedIt; // Iterator
    bool makeGraph = false; // Determine if graph needs to be made
    int count = 0;

    // gave the priority queue a lambda to determine the priority of a stadium
    priority_queue<Stadium*, vector<Stadium*>, function<bool(Stadium*, Stadium*)>>
        pending { [&dist](Stadium* lhs, Stadium* rhs){
        return dist[lhs->getStadiumName()] < dist[rhs->getStadiumName()];
    }};

    // Check first value


    // Determine if graph needs to be created
    for(visitedIt = visited.begin(); visitedIt != visited.end(); visitedIt++)
    {
        // Count the number of cities that have not been visited
        if(visitedIt.value() == true)
        {
            count++;
        }
    }

    // If any cities have visited, don't make the graph
    makeGraph = count != 0;

    // If it needs to be created, do that
    if(makeGraph)
    {
        // Create Graph
        for (auto node : graph.cities)
        {
            // Set distance at infinite
            dist[node->getStadiumName()] = numeric_limits<int>::max(); // (largest positive 32 bit #)
        }
    }

    //10      dist[start] ← 0
    dist[start->getStadiumName()] = 0;

    // loop thru start's adjacent vertices & add them to the pending list
    for (auto neighbor : graph.adjacencyList[start])
    {
        Stadium *toStadium = neighbor->getToStadium();
        dist[toStadium->getStadiumName()] = neighbor->getDistance();
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








    visitedIt = visited.find(start->getStadiumName());

    // Mark as visited
    visitedIt.value() = true;

    // Add to list
    tripList.push_back(visitedIt.key());

    // Find lowest cost. Add to QStringList of stadiumNames
    int lowest = numeric_limits<int>::max(); // Largest int
    QHash<QString, int>::iterator costsIt; // Iterator
    QHash<Stadium*, QVector<StadiumDistance*>>::const_iterator graphIt; // Iterator2
    Stadium* newStart = new Stadium;

    // For loop through costs array
    for(costsIt = dist.begin(); costsIt != dist.end(); costsIt++)
    {
        // If the stadium has not been visited
        visitedIt = visited.find(costsIt.key());

        // If the value is lower than the current value and has not been visited
        if(costsIt.value() < lowest && visitedIt.value() == false)
        {
            // Find that name in the graph and point to it
            for(graphIt = graph.adjacencyList.begin(); graphIt != graph.adjacencyList.end(); graphIt++)
            {
                // Point a pointer at this stadium
                if(costsIt.key() == graphIt.key()->getStadiumName())
                {
                    newStart = graphIt.key();
                }
            } // end inner loop
        }// end if
    }// end outer loop

    if(tripList.size() < visited.size())
    {
        return Helper(graph, newStart, visited, tripList);
    }
    else
    {
        return;
    }
}

