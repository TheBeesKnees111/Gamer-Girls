#ifndef BFS_H
#define BFS_H
#include <QString>
#include <QVector>

class AdjacencyMatrix
{
public:
    // City positions in list
    enum STADIUMS
    {
        SEATTLE, SAN_FRANCISCO, LOS_ANGELES, DENVER, KANSAS_CITY, DALLAS,
        CHICAGO, HOUSTON, ATLANTA, NEW_YORK, MIAMI, BOSTON
    };

    // Attributes
    int aMatrix [12][12]; // Adjacency matrix with distances
    bool visited [12] = { false }; // List of visited cities
    QVector<QString> cityNames; // List of city names

    // Methods
    void Add(const int &from, const int &to, const int &distance);

    AdjacencyMatrix();
};

class BFS
{
public:




    BFS();
};

#endif // BFS_H
