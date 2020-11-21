#include "StadiumGraph.h"
#include "mainwindow.h"

#include "Dijkstra.h"
#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;
//    testDijkstra();
    w.show();
    return a.exec();
}
