#include "StadiumGraph.h"
#include "mainwindow.h"

#include "Dijkstra.h"
#include <QApplication>
#include <iostream>
using namespace std;

void runDijkstra(const StadiumGraph& graph, QString start, QString end)
{
    Database* db = Database::getInstance();

    Stadium* startLocation{db->getStadiumByName(start)};
    Stadium* endLocation{db->getStadiumByName(end)};

    QHash<QString, StadiumDistance*> spanningTree = Dijkstra(graph, startLocation);
    QVector<StadiumDistance*> path = buildPath(spanningTree, endLocation);
    cout << "===================================================================" << endl;
    cout << "PATH FROM " << start.toStdString() << " to " << end.toStdString() << endl;
    cout << "===================================================================" << endl;
    printPath(path);

}

void testDijkstra()
{
    // Create Database
    Database* db = Database::getInstance();

    StadiumGraph graph = StadiumGraph::createStadiumGraph(db);
    graph.printAdjList();

    runDijkstra(graph, "Soldier Field", "Ford Field");
    runDijkstra(graph, "SoFi Stadium", "Bills Stadium");
    runDijkstra(graph, "SoFi Stadium", "Gillette Stadium");

    runDijkstra(graph, "Gillette Stadium", "Lincoln Financial Field");
    runDijkstra(graph, "Lincoln Financial Field", "Gillette Stadium");

    runDijkstra(graph, "Bank of America Stadium", "Gillette Stadium");
    runDijkstra(graph, "Allegiant Stadium", "Bills Stadium");
    runDijkstra(graph, "Allegiant Stadium", "CenturyLink Field");

}

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;
	//testDijkstra();
    w.show();
    return a.exec();
}
