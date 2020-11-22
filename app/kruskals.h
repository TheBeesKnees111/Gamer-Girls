#ifndef KRUSKALS_H
#define KRUSKALS_H

#include <QPair>
#include <QString>
#include <QMap>
#include <QVector>
#include <QDebug>
#include "Database.h"
#include "StadiumDistance.h"
#include "StadiumGraph.h"



//#define edge QPair<QString, QString>


class kruskals
{
private:
    QVector<StadiumDistance*> graph;
    QVector<StadiumDistance*> mst;
    QMap<Stadium*, Stadium*> parent;
    int TOTAL_VERTICES;
    int cost;
public:
    kruskals(int vertex);
   // void insertEdge(int w, QString u, QString v);
    void readDb(QString start);
    void print();
    Stadium* find_parent(Stadium *i);
    Stadium* union_set(Stadium* i, Stadium* v);
    void solve();
    static bool compareWeights(StadiumDistance *uno, StadiumDistance *dos);
};

#endif // KRUSKALS_H
