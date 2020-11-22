#include "kruskals.h"
#include <QSqlDatabase>

kruskals::kruskals(int vertex)
{
    cost = 0;
    for (int i = 0; i < vertex; i++)
    {
        graph.clear();
        mst.clear();
        TOTAL_VERTICES++;
    }
    qDebug() << TOTAL_VERTICES;
}

void kruskals::readDb(QString start)
{
    Database *Db = Database::getInstance();
    Stadium* startLocation{Db->getStadiumByName(start)};
    StadiumGraph newGraph = StadiumGraph::createStadiumGraph(Db);
    graph = Db->getStadiumDistances();
    for (auto stadium: graph)
    {
        parent[stadium->getFromStadium()] = stadium->getFromStadium();
        parent[stadium->getToStadium()] = stadium->getToStadium();
    }
  // newGraph.printAdjList();
}

Stadium* kruskals::find_parent(Stadium*i)
{
    if (parent[i] == i)
    {
        return i;
    }
    else
    {
        return  find_parent(parent[i]);
    }
}

Stadium* kruskals::union_set(Stadium* i, Stadium* v)
{
    parent[i] = parent[v];
}

void kruskals::solve()
{
    std::sort(graph.begin(), graph.end(), compareWeights);
    for (auto i: graph)
    {
        qDebug() << i->getToStadium()->getStadiumName() << "\n ";
    }
    for (int i = 0; i < graph.size(); i++)
    {
        Stadium* findSetOne = find_parent(graph[i]->getFromStadium());
        Stadium* findSetTwo = find_parent(graph[i]->getToStadium());
       if (findSetOne != findSetTwo)
        {
            mst.push_back(graph[i]);
            union_set(findSetOne, findSetTwo);
        }
    }
}

void kruskals::print()
{
    qDebug() << "Edge: " << " weight\n";
    for (int i = 0; i < mst.size(); i++)
    {
        qDebug() << mst[i]->getFromStadium()->getStadiumName() << " -> " << mst[i]->getToStadium()->getStadiumName() << ";";
    }
}

bool kruskals::compareWeights(StadiumDistance *uno, StadiumDistance *dos)
{
    return uno->getDistance() < dos->getDistance();
}
