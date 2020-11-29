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


class Database : public QSqlDatabase
{

public:
    // Database() constructor moved to private
    static Database *getInstance();

    // Enum for team statistics
//    enum TeamStats
//    {
//        T_ID, T_TEAM_NAME, T_STADIUM_NAME, T_SEATING_CAP, T_LOCATION,
//        T_CONFERENCE, T_DIVISION, T_SURFACE_TYPE, T_ROOF_TYPE, T_DATE_OPENED
//    };

    // TEAM METHODS
    Team *GetTeamByName(const QString name);

    // returns Team* object found by teamID
    Team* GetTeamByID(const int &teamID);

    // Uber object for use in all display sections. Will overwrite upon return to homepage
    QVector<Team*> GetTeams();  // TODO call in main window for initial setup

    // TODO Need to methods to update and create teams
    // They need to update the caches as well as the database


    //Return team name found by teamID
    QString GetTeamNameByID(const int& teamID);

    // not created in .cpp
    void    AddTeamToDatabase();


    // STADIUM METHODS
    // Creates stadiumDbCacheByID of Stadiums if they don't already exist.
    // Returns a vector of all Stadium*
    QVector<Stadium*> getStadiums();

    // return Stadium* found by teamID
    Stadium* getStadiumByID(const int& teamID);

    // return Stadium found by stadium name
    Stadium* getStadiumByName(const QString name);
    int      GetIDByStadiumName(const QString& stadiumName);

    // STADIUM DISTANCE METHODS
    // Checks to see if the stadiumDistanceCache is created.  If not, creates it.
    // Returns a vector edge list of (StadiumDistance*)
    QVector<StadiumDistance*> getStadiumDistances();

    // returns StadiumDistance found by distanceID
    StadiumDistance* getStadiumDistanceByID(int id);

    // SOUVENIR METHODS
    // For use in admin section
    QVector<Souvenir*> getSouvenirs();

    // For use in admin section
    Souvenir* getSouvenierByID(int souvenirID);
	void      AddDefaultSouvenirsToDatabase(int teamID,
											QStringList      souvenirs,
											QVector <double> prices);
	// PURCHASES METHODS
    // For use in admin section
    QVector<Purchases*> getPurchases();

    // For use in admin section
    Purchases* getPurchasesByID(int purchaseID);

    // DISTANCE METHODS
    int GetMilesBetweenStadiums(const QString &origin, const QString &destination);
    void AddDistancesToDataBaseFromFile(QString& stadiumName , QStringList& otherStadiums, QVector<int>& miles);

    /*!
     * @brief AddFood items to the database
     * @param city; Name of City in which Food will be added
     * @param food; Name of the Food item to be added
     * @param price; Price of Food item to be added
     */
    void AddSouvenir(const QString &team, const QString &souvenirName, const QString &price);

    /*!
     * @brief Updates food price in database
     * @param foodName; Name of food to be updated
     * @param price; New price of food item
     */
    void UpdateSouvenirPrice(const QString &SouvenirName, const QString teamName, const QString &price);

    /*!
     * @brief Deletes food listing from database
     * @param foodName; Name of food to be deleted
     */
    void DeleteSouvenir(const QString &SouvenirName, const QString &teamName);

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
    QVector<Team*>* CreateShoppingList(const QStringList &teamNames);

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
