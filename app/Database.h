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
    Stadium* getStadiumByID(int stadiumID);

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

    // TODO
    // should dijk call get miles from db
    // or create adjacency list & pass to dijk
    // creating the list will make dijk's algo run faster

private:
    QMap<int, Team*> teamDbMap;
    QMap<int, Stadium*> stadiumDbMap;
    QMap<int, Souvenir*> souvenirDbMap;
    QMap<int, Purchases*> purchasesDbMap;

    void runGetTeamAndStadiumByIDQry(int teamID);
    void runGetAllTeamsAndStadiums();

    QSqlQuery query;
};

#endif // DATABASE_H
