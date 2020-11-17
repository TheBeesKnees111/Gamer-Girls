#include "Dijkstra.h"
#include <iostream>

vector<string> Dijkstra(const StadiumGraph& graph, StadiumNode start, StadiumNode endLocation)
{
    //1  function Dijkstra(Graph, start):
    //2
    //3      create vertex set pending
    set<string> pending;
    map<string, int> dist;
    map<string, string> prev;

    //4
    //5      for each vertex v in Graph:
    for (auto node : graph.cities)
    {
        //6          dist[v] ← INFINITY
        dist[node.name] = 0x7fffffff; // (largest positive 32 bit #)
        //7          prev[v] ← UNDEFINED
        prev[node.name] = "";
        //8          add v to pending
        pending.insert(node.name);
    }

    //10      dist[start] ← 0
    dist[start.name] = 0;
    //11
    //12      while pending is not empty:
    while (!pending.empty())
    {
        //13          u ← vertex in pending with min dist[u]
        string u = *min_element(pending.begin(), pending.end(), [dist](string s1, string s2){
                return dist.at(s1) < dist.at(s2);
    });
        //14
        //15          remove u from pending
        pending.erase(u);
        //16
        //17          for each neighbor v of u:
        // only v that are still in pending
        for (auto v : graph.adjacencyList.at({u}))
        {
            //18              alt ← dist[u] + length(u, v)
            int alt = dist[u] + v.milesBetween;
            //19              if alt < dist[v]:
            if (alt < dist[v.fromStadium.name])
            {
                //20                  dist[v] ← alt
                dist[v.fromStadium.name] = alt;
                //21                  prev[v] ← u
                prev[v.fromStadium.name] = u;
            }
        }
        //22
    }
    //23      return dist[], prev[]

    //1  S ← empty sequence
    vector<string> S;
    //2  u ← endLocation
    string u = endLocation.name;
    //3  if prev[u] is defined or u = start:
    // Do something only if the vertex is reachable
    if(prev[u] != "")
    {
        //4      while u is defined:
        // Construct the shortest path with a stack S
        while (u != "")
        {
            //5          insert u at the beginning of S
            // Push the vertex onto the stack
            S.push_back(u);

            //6          u ← prev[u]
            // Traverse from endLocation to start
            u = prev[u];
        }
        reverse(S.begin(), S.end());
    }
    return S;
}


void printDijkstra(vector<string> path)
{
    cout << "Shortest path: ";
    for (auto cityName : path)
    {
        cout << cityName << " ";
    }
}

bool operator< (const StadiumNode& lhs, const StadiumNode& rhs)
{
    return (lhs.name < rhs.name);
}
