#ifndef BFS_H
#define BFS_H
#include <QString>
#include <QVector>
#include <QStringList>

class BFS
{
public:
    // City positions in list
//    enum Stadiums
//    {
//        ARIZONA, ATLANTA, BALTIMORE, BUFFALO, CAROLINA, CHICAGO, CINCINNATI,
//        CLEVELAND, DALLAS, DENVER, DETROIT, GREEN_BAY, HOUSTON, INDIANAPOLIS,
//        JACKSONVILLE, KANSAS_CITY, LOS_ANGELES, MIAMI, MINNESOTA, NEW_ENGLAND,
//        NEW_ORLEANS, NEW_YORK, LAS_VEGAS, PHILADELPHIA, PITTSBURGH, SAN_FRANCISCO,
//        SEATTLE, TAMPA_BAY, TENNESSEE, WASHINGTON
//    };

    // TEST DATA
    enum cities
    {
        SEATTLE, SAN_FRANCISCO, LOS_ANGELES, DENVER, KANSAS_CITY, DALLAS,
        CHICAGO, HOUSTON, ATLANTA, NEW_YORK, MIAMI, BOSTON
    };

    // Attributes
    int matrix [12][12]; // Adjacency matrix with distances
    bool visited [12] = { false }; // List of visited cities
    QStringList* stadiumNames; // List of city names

    // Methods
    void Add(const int &from, const int &to, const int &distance);

    void Resize();

    void Traverse();

    BFS();
};

#endif // BFS_H
