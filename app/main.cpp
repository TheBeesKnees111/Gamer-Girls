#include "StadiumGraph.h"
#include "mainwindow.h"
#include "DFS.h"
#include "Dijkstra.h"
#include <QApplication>
#include <iostream>
using namespace std;

// Creates and prints the specified path for Dijkstra
void runDijkstra(const StadiumGraph& graph, QString start, QString end)
{
    Database* db = Database::getInstance();

    Stadium* startLocation{db->getStadiumByName(start)};
    Stadium* endLocation{db->getStadiumByName(end)};

    QHash<QString, StadiumDistance*> spanningTree = Dijkstra(graph, startLocation);
    QVector<StadiumDistance*> path = buildPath(spanningTree, endLocation);
    cout << "===================================================================" << endl;
    cout << "DIJKSTRA PATH FROM " << start.toStdString() << " to " << end.toStdString() << endl;
    cout << "===================================================================" << endl;
    printPath(path);
}

// Runs / calls various paths for Dijkstra
void testDijkstra()
{
    // Create Database
    Database* db = Database::getInstance();

    StadiumGraph graph = StadiumGraph::createStadiumGraph(db);
//    graph.printAdjList();

//    runDijkstra(graph, "Soldier Field", "Ford Field");
//    runDijkstra(graph, "SoFi Stadium", "Bills Stadium");
//    runDijkstra(graph, "SoFi Stadium", "Gillette Stadium");
//    runDijkstra(graph, "Gillette Stadium", "Lincoln Financial Field");
//    runDijkstra(graph, "Lincoln Financial Field", "Gillette Stadium");
//    runDijkstra(graph, "Bank of America Stadium", "Gillette Stadium");
//    runDijkstra(graph, "Allegiant Stadium", "Bills Stadium");
//    runDijkstra(graph, "Lambeau Field", "Hard Rock Stadium");
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

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;

    // TEST FOR DIJKSTRA & DFS
//    testDijkstra();
    testDFS();
    // END TEST

    w.show();
    return a.exec();
}
