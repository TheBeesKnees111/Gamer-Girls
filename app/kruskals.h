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



class kruskals
{
private:
    /*
     *      Private member functions
     */
    //creates graph of stadiums
    QVector<StadiumDistance*> graph;
    //creates the mst of stadiums
    QVector<StadiumDistance*> mst;
    //holds the parent values of each to and from stadium
    QMap<Stadium*, Stadium*> parent;
    //total number of vertices in the graph
    int TOTAL_VERTICES;
    //total cost of the mst->total distance traveled
    int cost;
    //holds the team names->used for output when printing the mst trip
    QVector<Team*> teamNames;
    //a qstring  list to populate the data to the display trip class
    QStringList traversalList;
public:
    /*
     *      Public member functions
     */
    //constructor-> is instantiated by a number of vertices, I used a default value of 10,000 in the souvenir and trip class
    kruskals(int vertex);
    //Grab data from db
    void readDb(QString start);
    //print the mst
    void print();
    //calc cost of the mst
    int calcCost();
    //find the parent values of the to and from stadiums
    Stadium* find_parent(Stadium *i);
    //check for loops/cycles in mst
    Stadium* union_set(Stadium* i, Stadium* v);
    //solve kruskals algorithm
    void solve();
    //comparator to sort the distances for the "greedy method"
    static bool compareWeights(StadiumDistance *uno, StadiumDistance *dos);
    //return total distance traveled
    int getDistanceTraveled() const;
    //return the list of team names as  a qstringlist
    QStringList getList() const;
};

#endif // KRUSKALS_H
