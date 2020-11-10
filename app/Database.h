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

    // TODO FINISH THIS ENUM
    enum TeamStats { T_ID, T_NAME };

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
