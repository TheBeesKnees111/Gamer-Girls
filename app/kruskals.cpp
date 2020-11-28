#include "kruskals.h"
#include <QSqlDatabase>


kruskals::kruskals(int vertex)
{
    //set cost to 0
    cost = 0;
    for (int i = 0; i < vertex; i++)
    {
        //clear the mst and graph
        graph.clear();
        mst.clear();
        //inc total vertices because new vertex is made
        TOTAL_VERTICES++;
    }
}

void kruskals::readDb(QString start)
{
    //provide singleton test for db-> make sure db is only instantiated once
    Database *Db = Database::getInstance();
    //get the start location
    Stadium* startLocation{Db->getStadiumByName(start)};
    //create graph
    StadiumGraph newGraph = StadiumGraph::createStadiumGraph(Db);
    graph = Db->getStadiumDistances();
    //set parent values to the to and from stadiums respectively
    for (auto stadium: graph)
    {
        parent[stadium->getFromStadium()] = stadium->getFromStadium();
        parent[stadium->getToStadium()] = stadium->getToStadium();
    }
}

Stadium* kruskals::find_parent(Stadium*i)
{
    //if our index is the value passed in-> return value passed in because the search is complete
    if (parent[i] == i)
    {
        return i;
    }
    //else recursively call until parameter is found
    else
    {
        return  find_parent(parent[i]);
    }
}

Stadium* kruskals::union_set(Stadium* i, Stadium* v)
{
    //check for cycles and loops
    parent[i] = parent[v];
}

void kruskals::solve()
{
    //sort values from smallest to largest
    std::sort(graph.begin(), graph.end(), compareWeights);
    for (int i = 0; i < graph.size(); i++)
    {
        //find the parent of our first stadium
        Stadium* findSetOne = find_parent(graph[i]->getFromStadium());
        //find parent of second stadium
        Stadium* findSetTwo = find_parent(graph[i]->getToStadium());
        //if the parents are not equal-> push back the value at i into the mst
       if (findSetOne != findSetTwo)
        {
            mst.push_back(graph[i]);
            //check for cycles
            union_set(findSetOne, findSetTwo);
        }
    }
    //push back our values into our qstringlist-> used in sovenir and trip class
    for (int i = 0; i < mst.size(); i++)
    {
           traversalList.push_back(mst[i]->getFromStadium()->getStadiumName());
           traversalList.push_back(mst[i]->getToStadium()->getStadiumName());
    }
}

int kruskals::calcCost()
{
    //calculate the cost at each value of the mst
    for (int i = 0; i < mst.size(); i++)
    {
        cost += mst[i]->getDistance();
    }
    //return cost
    return cost;
}

int  kruskals::getDistanceTraveled() const
{
    //return cost
    return cost;
}

QStringList kruskals::getList() const
{
    //return the list
    return traversalList;
}

bool kruskals::compareWeights(StadiumDistance *uno, StadiumDistance *dos)
{
    //return the smaller distance so we can sort
    return uno->getDistance() < dos->getDistance();
}
