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

/*!
 * @class kruskals
 * @brief The Kruskals class contains all objects necessary to kruskals algorithm to create minimum spanning tree
 */
class kruskals
{
private:
    /// Graph to reference during traversal
    QVector<StadiumDistance*> graph;
    /// Minimum spanning tree created during traversal
    QVector<StadiumDistance*> mst;
    /// Parent values of each 'to' and 'from' stadium
    QMap<Stadium*, Stadium*> parent;
    /// Total number of vertices in the graph
    int TOTAL_VERTICES;
    /// Total distance traveled during traversal
    int cost;
    /// List of teamnames to output during traversal
    QVector<Team*> teamNames;
    /// Final list of stadiums visited in traversal order
    QStringList traversalList;
public:

    /*!
     * @brief Parameterized Constructor
     * @param vertex; Number of vertices used in traversal
     */
    kruskals(int vertex);

    /*!
     * @brief Read necessary data from database
     * @param start; Starting vertex
     */
    void readDb(QString start);

    /*!
     * @brief Print minimum spanning tree
     */
    void print();

    /*!
     * @brief Calculates and returns total cost of MST
     * @return int; Total cost of MST
     */
    int calcCost();

    //find the parent values of the to and from stadiums
    /*!
     * @brief Returns parent of child stadium
     * @param i; Child in need of parent information
     * @return Stadium*; Pointer to parent of stadium input
     */
    Stadium* find_parent(Stadium *i);

    /*!
     * @brief Checks for loops during traversal
     * @param i; Origin vertex
     * @param v; Destination vertex
     * @return Stadium*; Stadium detected in loop
     */
    Stadium* union_set(Stadium* i, Stadium* v);

    /*!
     * @brief Perform traversal
     */
    void solve();

    //comparator to sort the distances for the "greedy method"

    /*!
     * @brief Comparator to compare weights between stadiums
     * @param uno; First stadium to compare
     * @param dos; Second stadium to compare
     * @return bool; Returns whether or not stadium contains shorter cost
     */
    static bool compareWeights(StadiumDistance *uno, StadiumDistance *dos);

    /*!
     * @brief Accessor returns distance traveled during traversal
     * @return int; Distance traveled during traversal
     */
    int getDistanceTraveled() const;

    /*!
     * @brief Returns list of stadium names in order of traversal
     * @return QStringList; Stadium names in order of traversal
     */
    QStringList getList() const;
};

#endif // KRUSKALS_H
