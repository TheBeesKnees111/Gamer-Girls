#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QObject>
#include <QDebug>
#include <QSqlQuery>

class Team;
class Souvenir;
class Stadium;
class Purchases;

class Database : public QSqlDatabase
{

public:

    Database();

    // Enum for team statistics
    enum TeamStats
    {
        T_ID, T_TEAM_NAME, T_STADIUM_NAME, T_SEATING_CAP, T_LOCATION,
        T_CONFERENCE, T_DIVISION, T_SURFACE_TYPE, T_ROOF_TYPE, T_DATE_OPENED
    };

    // TEAM METHODS
    Team* GetTeamByID(const int &teamID);
    QVector<Team*> GetTeams();

    // STADIUM METHODS
    QVector<Stadium*> getStadiums();
	Stadium* getStadiumByID(const int& teamID);

    // SOUVENIR METHODS
    QVector<Souvenir*> getSouvenirs();
    Souvenir* getSouvenierByID(int souvenirID);

    // PURCHASES METHODS
    QVector<Purchases*> getPurchases();
    Purchases* getPurchasesByID(int purchaseID);

    // DISTANCE METHODS
    int GetMilesBetweenStadiums(const QString &origin, const QString &destination);

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
    QVector<Team>* GetTeamsOrderByName();

    // Get all teams and stadiums ordered by stadium name (Requirement 4)
    QVector<Team>* GetTeamsOrderByStadium();

    // Get all AFC Teams sorted by team name (Requirement 5)
    QVector<Team>* GetAFCTeamsOrderByTeamName();

    // Get all NFC teams sorted by team name (Requirement 6)
    QVector<Team>* GetNFCTeamsOrderByTeamName();

    // Get all NFC North teams ordered by team name (Requirement 7)
    QVector<Team>* GetNorthNFCTeamsOrderByTeamName();

    // Get all stadiums sorted by date opened (Requirement 8)
    QVector<Team>* GetStadiumsOrderByDateOpened();

    // Get all open roof stadiums (Requirement 9)
    QVector<Team>* GetOpenRoofStadiums();

    // Get stadiums ordered by seating capacity (Requirement 10)
    QVector<Team>* GetStadiumsOrderBySeatingCap();

    // Get teams ordered by conference (Requirement 11)
    QVector<Team>* GetTeamsOrderByConference();

    // Get teams with bermuda grass surface type (Requirement 12)
    QVector<Team>* GetBermudaGrassTeams();

    // Get all souvenirs for one team (Requirement 13)
    Team* GetSingleTeamSouvenirs(const QString &teamName);

    // TODO
    // should dijk call get miles from db
    // or create adjacency list & pass to dijk
    // creating the list will make dijk's algo run faster

private:
	QMap<int, Team*>      teamDbMap;
	QMap<int, Stadium*>   stadiumDbMap;
	QMap<int, Souvenir*>  souvenirDbMap;
    QMap<int, Purchases*> purchasesDbMap;

    void runGetTeamAndStadiumByIDQry(int teamID);
    void runGetAllTeamsAndStadiums();

    QSqlQuery query;
};

#endif // DATABASE_H
