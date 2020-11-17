#include "StadiumGraph.h"

// This creates a graph of Stadiums.  It is an adjacency list made
// using a map of vectors.  The key for each entry is the Stadium,
// and the value is a vector of adjacent edges (StadiumDistances).
StadiumGraph StadiumGraph::createStadiumGraph(Database *db)
{
    QVector<StadiumDistance*> edgeList = db->getStadiumDistances();
    QHash<Stadium*, QVector<StadiumDistance*>> adjacencyList;

    // Adjacency list from the edge list
    for(auto edge : edgeList)
    {
        Stadium* fromStadium = edge->getFromStadium();
        //        Stadium* toStadium = edge->getToStadium();
        //        int milesBetween = edge->getDistance();

        // Creates adjacencyList if it doesn't already exist
        adjacencyList[fromStadium].push_back(edge);
        // creating the reverse edge
        //        adjacencyList[toStadium].push_back(edge);
    }
    // creating graph when returning
    return {db->getStadiums(), adjacencyList};
}
