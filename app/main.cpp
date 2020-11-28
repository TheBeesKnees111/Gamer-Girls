#include "mainwindow.h"
#include "Dijkstra.h"
#include "kruskals.h"
#include <QApplication>
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication a(argc, argv);
    MainWindow w;
   // testDijkstra();
	qDebug() << "***************Creating object*****************\n";
	kruskals g(100);
	g.print();
	qDebug() << "***************Print 1*****************\n";

	qDebug() << "***************Pre readDB*****************\n";
	g.readDb("SoFi Stadium");
	g.print();
	qDebug() << "***************Print 2*****************\n";

	qDebug() << "***************pre solve*****************\n";
	g.solve();
	g.print();
	qDebug() << "***************Print 3*****************\n";


    w.show();
    return a.exec();
}
