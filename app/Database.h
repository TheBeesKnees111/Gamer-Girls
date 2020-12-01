#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
#include <QtCore>
#include <vector>
#include "StadiumDistance.h"
using namespace std;
#include <QVector>

class Team;
class Souvenir;
class Stadium;
class Purchases;
class AdjacencyList;

/*!
 * @class Database
 * @brief The Database class manages core methods used to access the data stored in the database
 */
class Database : public QSqlDatabase
{

public:
    /*!
     * @brief Creates one instance of the database
     * @return Pointer the the instance of the database class
     */
    static Database *getInstance();

    /*!
     * @brief Accessor returns team based on name
     * @param name; Name of team desired
     * @return Team*; Team object
     */
    Team* GetTeamByName(const QString name);

    /*!
     * @brief Accessor returns team based on ID
     * @param teamID; ID of team desired
     * @return Team*; Team object
     */
    Team* GetTeamByID(const int &teamID);

    /*!
     * @brief Accessor returns all team objects
     * @return; QVector<Team*>; Container of team objects
     */
    QVector<Team*> GetTeams();

    /*!
     * @brief Accessor returns team name by teamID
     * @param teamID; ID of team desired
     * @return QString; Team name
     */
    QString GetTeamNameByID(const int& teamID);

    /*!
     * @brief Accessor returns container of all stadium objects
     * @return QVector<Stadium*>; Container of all stadium objects
     */
    QVector<Stadium*> getStadiums();

    /*!
     * @brief Accessor returns stadium object based on team ID
     * @param teamID; ID of team belonging to stadium desired
     * @return Stadium*; Stadium object
     */
    Stadium* getStadiumByID(const int& teamID);

    /*!
     * @brief Accessor returns stadium object based on stadium name
     * @param name; Name of stadium desired
     * @return Stadium*; Stadium object
     */
    Stadium* getStadiumByName(const QString name);

    /*!
     * @brief Accessor returns ID of stadium based on stadium name
     * @param stadiumName; Name of stadium desired
     * @return int; Stadium ID
     */
    int      GetIDByStadiumName(const QString& stadiumName);

    /*!
     * @brief Accessor returns distances from each stadium to each other
     * @return QVector<StadiumDistance*>; Container of stadium distances
     */
    QVector<StadiumDistance*> getStadiumDistances();

    /*!
     * @brief Accessor returns distances contained at desired vertex based on ID
     * @param id; Desired stadium's ID
     * @return StadiumDistance*; Distances from desired vertex's ID
     */
    StadiumDistance* getStadiumDistanceByID(int id);

    /*!
     * @brief Adds desired team's default souvenirs to database
     * @param teamId; Desired team's ID
     * @param souvenirs; List of souvenirs
     * @param prices; Prices of souvenirs
     */
	void      AddDefaultSouvenirsToDatabase(int teamID,
											QStringList      souvenirs,
											QVector <double> prices);
    /*!
     * @brief Accessor to retrieve distance between stadiums
     * @param origin; Origin vertex
     * @param destination; Destination vertex
     * @return int; Distance between vertices
     */
    int GetMilesBetweenStadiums(const QString &origin, const QString &destination);

    /*!
     * @brief Adds distances between new stadiums and old stadiums from file
     * @param stadiumName; Name of new stadium
     * @param otherStadiums; List of other stadiums' names
     * @param miles; Container of other stadiums' distances
     */
    void AddDistancesToDataBaseFromFile(QString& stadiumName , QStringList& otherStadiums, QVector<int>& miles);

    /*!
     * @brief Accessor to retrieve names of teams in database
     * @return QStringList; Names of teams in database
     */
    QStringList GetTeamNames();

    /*!
     * @brief Accessor to retrieve all statistics of single team (Requirement 2)
     * @param teamName; Name of team desired
     * @return Team*; Team object desired
     */
    Team* GetSingleTeam(const QString &teamName);

    /*!
     * @brief Accessor to retrieve all teams ordered by team name (Requirement 3)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetTeamsOrderByName();

    /*!
     * @brief Accessor to retrieve all teams and stadiums ordered by stadium name (Requirement 4)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetTeamsOrderByStadium();

    /*!
     * @brief Accessor to retrieve all AFC Teams sorted by team name (Requirement 5)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetAFCTeamsOrderByTeamName();

    /*!
     * @brief Accessor to retrieve all NFC teams sorted by team name (Requirement 6)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetNFCTeamsOrderByTeamName();

    /*!
     * @brief Accessor to retrieve all NFC North teams sorted by team name (Requirement 7)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetNorthNFCTeamsOrderByTeamName();

    /*!
     * @brief Accessor to retrieve all stadiums sorted by date opened (Requirement 8)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetStadiumsOrderByDateOpened();

    /*!
     * @brief Accessor to retrieve all open roof stadiums (Requirement 9)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetOpenRoofStadiums();

    /*!
     * @brief Accessor to retrieve number of open roof stadiums (Requirement 9)
     * @return int; Number of open roof stadiums
     */
    int GetOpenStadiumCount();

    /*!
     * @brief Accessor to retrieve all stadiums ordered by seating capacity (Requirement 10)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetStadiumsOrderBySeatingCap();

    /*!
     * @brief Accessor to retrieve total seating capacity of entire NFL (Requirement 10)
     * @return int; Total seating capacity of all stadiums combined
     */
    int GetTotalSeatingCapacity();

    /*!
     * @brief Accessor to retrieve all teams ordered by conference (Requirement 11)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetTeamsOrderByConference();

    /*!
     * @brief Accessor to retrieve all teams with bermuda grass surface type (Requirement 12)
     * @return QVector<Team*>*; Team objects desired
     */
    QVector<Team*>* GetBermudaGrassTeams();

    /*!
     * @brief Accessor to retrieve total total bermuda grass stadiums (Requirement 12)
     * @return int; Total stadiums with Bermuda Grass turf
     */
    int GetBermudaGrassTeamCount();

    /*!
     * @brief Accessor to retrieve all souvenirs for one team (Requirement 13)
     * @param teamName; Name of team whose souvenirs are desired
     * @return Team*; Team objects desired
     */
    Team* GetSingleTeamSouvenirs(const QString &teamName);

    /*!
     * @brief Creates and returns adjacency list used for algorithms
     * @return AdjacencyList*; Adjacency list used for algorithms
     */
    AdjacencyList* GetAdjacencyList();

    /*!
     * @brief Creates and returns traversal list and shopping cart for stadiums on trip
     * @param stadiumNames; Stadiums on trip
     * @return QVector<Team*>*; Populated team list used for shopping cart
     */
    QVector<Team*>* CreateShoppingList(const QStringList &stadiumNames);

    // Write purchase info to db

    /*!
     * @brief Saves customer's purchase to database
     * @param teamList; Details of customer purchase
     */
    void SavePurchase(QVector<Team*>* teamList);


private:
    /*!
     * @brief Constructor private because singleton pattern
     */
    Database();

    /// Pointer to static pointer used for singleton
    static Database *instance;
    /// Default query to use in database
    QSqlQuery query;
    /// Team sorted by ID
    QMap<int, Team*>            teamDbCache;
    /// Team cache sorted by name
    QMap<QString, Team*>        teamDbCacheByName;
    /// Stadium cache sorted by name
    QMap<QString, Stadium*>     stadiumDbCacheByName;
    /// Stadium cache sorted by ID
    QMap<int, Stadium*>         stadiumDbCacheByID;
    /// Stadium distances sorted by ID
    QMap<int, StadiumDistance*> stadiumDistanceCache;
    /// Souvenir cache sorted by ID
    QMap<int, Souvenir*>        souvenirDbCache;
    /// Purchase cache sorted by ID
    QMap<int, Purchases*>       purchasesDbCache;

    /*!
     * @brief Creates new memory caches of teams and stadiums each time team or stadium is requested
     */
    void runGetAllTeamsAndStadiums();

    /*!
     * @brief Creates new memory caches of stadiums and their distances
     */
    void runGetAllStadiumDistances();
};

#endif // DATABASE_H
