#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <map>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
#include <string>
using namespace std;


// Node of a city
struct StadiumNode
{
    string name;
};

bool operator< (const StadiumNode& lhs, const StadiumNode& rhs);

// Connection between two cities
struct StadiumConnection
{
    StadiumNode fromStadium;
    StadiumNode toStadium;
    int         milesBetween;
};

// Graph of cities and their connections
struct StadiumGraph
{
    vector<StadiumNode> cities;
    map<StadiumNode, vector<StadiumConnection>> adjacencyList;
};

vector<string> Dijkstra(const StadiumGraph& graph, StadiumNode start, StadiumNode endLocation);

void printDijkstra(vector<string> path);

#endif // DIJKSTRA_H
