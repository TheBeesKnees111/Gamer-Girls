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
 * @class DBManager
 * @brief The DBManager class manages core methods used to access the data stored in the database
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
     * @brief Will return team based on name
     * @param name; Name of team desired
     * @return Team*; Team object
     */
    Team* GetTeamByName(const QString name);

    /*!
     * @brief Will return team based on ID
     * @param teamID; ID of team desired
     * @return Team*; Team object
     */
    Team* GetTeamByID(const int &teamID);

    /*!
     * @brief Will return all teams
     * @return; QVector<Team*>; Container of team objects
     */
    QVector<Team*> GetTeams();

    /*!
     * @brief Will return team name by teamID
     * @param teamID; ID of team desired
     * @return QString; Team name
     */
    QString GetTeamNameByID(const int& teamID);

    /*!
     * @brief Will return container of all stadium objects
     * @return QVector<Stadium*>; Container of all stadium objects
     */
    QVector<Stadium*> getStadiums();

    /*!
     * @brief Will return stadium object based on team ID
     * @param teamID; ID of team belonging to stadium desired
     * @return Stadium*; Stadium object
     */
    Stadium* getStadiumByID(const int& teamID);

    /*!
     * @brief Will return stadium object based on stadium name
     * @param name; Name of stadium desired
     * @return Stadium*; Stadium object
     */
    Stadium* getStadiumByName(const QString name);

    /*!
     * @brief Will return ID of stadium based on stadium name
     * @param stadiumName; Name of stadium desired
     * @return int; Stadium ID
     */
    int      GetIDByStadiumName(const QString& stadiumName);

    // STADIUM DISTANCE METHODS
    // Checks to see if the stadiumDistanceCache is created.  If not, creates it.
    // Returns a vector edge list of (StadiumDistance*)


    QVector<StadiumDistance*> getStadiumDistances();

    // returns StadiumDistance found by distanceID
    StadiumDistance* getStadiumDistanceByID(int id);

	void      AddDefaultSouvenirsToDatabase(int teamID,
											QStringList      souvenirs,
											QVector <double> prices);


    // DISTANCE METHODS
    int GetMilesBetweenStadiums(const QString &origin, const QString &destination);
    void AddDistancesToDataBaseFromFile(QString& stadiumName , QStringList& otherStadiums, QVector<int>& miles);

    /*
     * DisplayInfo.ui Information Retrieval Methods
     */

    // Get team names
    QStringList GetTeamNames();

    // Get Info for one team (Requirement 2)
    Team* GetSingleTeam(const QString &teamName);

    // Get all teams ordered by team name (Requirement 3)
    QVector<Team*>* GetTeamsOrderByName();

    // Get all teams and stadiums ordered by stadium name (Requirement 4)
    QVector<Team*>* GetTeamsOrderByStadium();

    // Get all AFC Teams sorted by team name (Requirement 5)
    QVector<Team*>* GetAFCTeamsOrderByTeamName();

    // Get all NFC teams sorted by team name (Requirement 6)
    QVector<Team*>* GetNFCTeamsOrderByTeamName();

    // Get all NFC North teams ordered by team name (Requirement 7)
    QVector<Team*>* GetNorthNFCTeamsOrderByTeamName();

    // Get all stadiums sorted by date opened (Requirement 8)
    QVector<Team*>* GetStadiumsOrderByDateOpened();

    // Get all open roof stadiums (Requirement 9)
    QVector<Team*>* GetOpenRoofStadiums();

    // Get number of open roof stadiums (Requirement 9)
    int GetOpenStadiumCount();

    // Get stadiums ordered by seating capacity (Requirement 10)
    QVector<Team*>* GetStadiumsOrderBySeatingCap();

    // Get total seating capacity of entire NFL (Requirement 10)
    int GetTotalSeatingCapacity();

    // Get teams ordered by conference (Requirement 11)
    QVector<Team*>* GetTeamsOrderByConference();

    // Get teams with bermuda grass surface type (Requirement 12)
    QVector<Team*>* GetBermudaGrassTeams();

    // Get total bermuda grass stadiums (Requirement 12)
    int GetBermudaGrassTeamCount();

    // Get all souvenirs for one team (Requirement 13)
    Team* GetSingleTeamSouvenirs(const QString &teamName);

    // Get adjacency list for algorithms
    AdjacencyList* GetAdjacencyList();

    // Populate Shopping Cart List
    QVector<Team*>* CreateShoppingList(const QStringList &stadiumNames);

    // Write purchase info to db
    void SavePurchase(QVector<Team*>* teamList);


private:
    // Moved so that outside code can't call the constructor & must call getInstance
    Database();
    static Database *instance;  // this is the singleton pattern
    QSqlQuery query;


    // these maps cache the values of these queries so we only have to run them once
    QMap<int, Team*>            teamDbCache;
    QMap<QString, Team*>        teamDbCacheByName;
    QMap<QString, Stadium*>     stadiumDbCacheByName;
    QMap<int, Stadium*>         stadiumDbCacheByID;
    QMap<int, StadiumDistance*> stadiumDistanceCache;
    QMap<int, Souvenir*>        souvenirDbCache;
    QMap<int, Purchases*>       purchasesDbCache;

    // This will run whenever a team or stadium is requested to ensure the
    // caches are populated.  Once created, they don't need to be created again.
    // Creates QMap caches of team and stadium objects.
    // These can then be used thruout the application whenever needed.
    // Creates teamDbCache, stadiumDbCacheByName, & stadiumDbCacheByID
    void runGetAllTeamsAndStadiums();

    // creates stadiumDistanceCache for all StadiumDistances if it doesn't already exist
    void runGetAllStadiumDistances();
};

#endif // DATABASE_H
